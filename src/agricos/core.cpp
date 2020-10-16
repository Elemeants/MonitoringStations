#include "core.h"

#include <avr/wdt.h>

#include "cli.h"
#include "devices.h"
#include "error_codes.h"
#include "sensors.h"
#include "style.h"

#define doUntilTimeElapsed(__time_handler, __ms_elapsed, __function) \
    static uint32_t __time_handler = 0;                              \
    if (__time_handler > millis())                                   \
    {                                                                \
        __time_handler = millis();                                   \
    }                                                                \
    if ((millis() - __time_handler) > __ms_elapsed)                  \
    {                                                                \
        __time_handler = millis();                                   \
        __function                                                   \
    }

AgricosCore_Status_t AgricosSysStatus;

static _JsonMeasureRegister JSONOutput;
StaticJsonDocument<JSON_STATIC_RAM_SIZE> jsonFileRoot;
_MeasureRegister *MeasureRegister = &JSONOutput;

_SensorsRegister SensorsRegister;

_ITaskRegister PostLoopTaskRegister;
_ITaskRegister PreLoopTaskRegister;
_ITaskRegister SetupTasksRegister;

void (*AgricosCore_onFail)(void) __attribute__((weak)) = NULL;
void (*AgricosCore_onSuccess)(void) __attribute__((weak)) = NULL;
bool (*AgricosCore_OutputTask)(void) __attribute__((weak)) = NULL;

void throw_error(uint8_t errorCode)
{
    switch (errorCode)
    {
    case AGRICOS_ERROR_TIME_PROVIDER_NOT_DEFINED:
        logger << LOG_ERROR << F("TimeProvider is not defined") << EndLine;
        break;
    case AGRICOS_ERROR_OUT_FUNCTION_NOT_DEFINED:
        logger << LOG_ERROR << F("Output function is not defined") << EndLine;
        break;
    default:
        logger << LOG_ERROR << F("Error ocurred... reseting device") << EndLine;
        break;
    }
    while (1)
        ;
}

void initVariant(void)
{
    logger.begin();
    eLogLevel_t lv = Configuration::readLogLevel();
    logger.setLogLevel(lv);
    logger.println();
}

void AgricosCore_InitRegisters(void)
{
    MeasureRegister->init();
}

void AgricosCore_Init(void)
{
    AgricosStyle_PrintAsciiLogo(logger);

    logger << LOG_MASTER << LOGGER_TEXT_BOLD << F("------------------ Initializing Agricos ------------------") << EndLine;
    Configuration::init();

    AgricosSysStatus.sysRtcMode = (eRtcMode_t)Configuration::readRTCMode();

    logger << LOG_MASTER << F("Initializing I2C Drivers") << EndLine;
    I2CBus.begin();

    logger << LOG_MASTER << F("Initializing I2C Scan") << EndLine;
    I2CBus.scan();

    AgricosDevices_Init();

    logger << LOG_MASTER << F("Executing setup tasks") << EndLine;
    SetupTasksRegister.run();

    logger << LOG_MASTER << F("Executing sensors setup tasks") << EndLine;
    SensorsRegister.setup();

    logger << LOG_MASTER << F("Configuring CLI Interface") << EndLine;
    AgricosCli_Setup();

    if (!TimeProvider)
    {
        throw_error(AGRICOS_ERROR_TIME_PROVIDER_NOT_DEFINED);
    }

    if (!AgricosCore_OutputTask)
    {
        throw_error(AGRICOS_ERROR_OUT_FUNCTION_NOT_DEFINED);
    }

    logger << LOG_MASTER << F("Executing loop...") << EndLine;
    while (1)
    {
        AgricosCore_Task();
    }
}

static void AgricosCore_UpdateDateTime(void)
{
    TimeProvider->update();
    AgricosSysStatus.sysTime = TimeProvider->getTime();
    logger.setLogTime(AgricosSysStatus.sysTime);
}

static bool AgricosCore_SendDataTrigger(void)
{
    Time_s time = TimeProvider->getTime();
    switch (AgricosSysStatus.sysRtcMode)
    {
    case RTC_30_MINUTES:
        return time.minute % 30 == 0;
    case RTC_15_MINUTES:
        return time.minute % 15 == 0;
    case RTC_2_MINUTES:
        return time.minute % 2 == 0;
    default:
        return true;
    }
}

void AgricosCore_Task(void)
{
    static bool Agricos_isSended = false;
    AgricosSysStatus.sysMilliseconds = millis();
#if ENABLE_STATUS_LED
    doUntilTimeElapsed(__blink_led_handler, 250, {
        StatusLed::blink();
    });
#endif
    doUntilTimeElapsed(__update_rtc_handler, 1000, {
        AgricosCore_UpdateDateTime();
    });

    AgricosCli_CheckCommands();

    bool send = AgricosCore_SendDataTrigger();

    if (send && !Agricos_isSended)
    {
        Agricos_isSended = true;

        logger << LOG_MASTER << LOGGER_TEXT_YELLOW << F("Executing PreLoopTask") << EndLine;
        PreLoopTaskRegister.run();

        logger << LOG_MASTER << LOGGER_TEXT_YELLOW << F("Executing MeasureRegister Init") << EndLine;
        MeasureRegister->init();

        logger << LOG_MASTER << LOGGER_TEXT_YELLOW << F("Executing Sensors Reg") << EndLine;
        SensorsRegister.run();

        if (AgricosCore_OutputTask())
        {
            AgricosSysStatus.suceessMeasures++;
            if (AgricosCore_onSuccess)
            {
                AgricosCore_onSuccess();
            }
        }
        else
        {
            if (AgricosCore_onFail)
            {
                AgricosCore_onFail();
            }
        }

        logger << LOG_MASTER << LOGGER_TEXT_YELLOW << F("Executing PostLoopTask") << EndLine;
        PostLoopTaskRegister.run();
        AgricosSysStatus.measuresTaked++;
    }
    else if (!send)
    {
        Agricos_isSended = false;
    }
}