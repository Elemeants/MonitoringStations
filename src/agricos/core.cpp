#include "core.h"

#include <avr/wdt.h>

#include "cli.h"
#include "devices.h"
#include "error_codes.h"
#include "sensors.h"
#include "style.h"

static eRtcMode_t Agricos_rtcMode;
static bool Agricos_isSended;

static uint32_t Agricos_noMeasures = 0;
static uint32_t Agricos_SuccessMeasures = 0;
static uint32_t last_blink = 0;

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

    logger << LOG_MASTER << LOGGER_TEXT_BOLD << LOGGER_TEXT_GREEN << F("------------------ Initializing Agricos ------------------") << EndLine;
    Configuration::init();

    Agricos_rtcMode = (eRtcMode_t)Configuration::readRTCMode();

    logger << LOG_MASTER << LOGGER_TEXT_GREEN << F("Initializing I2C Drivers") << EndLine;
    I2CBus.begin();

    logger << LOG_MASTER << LOGGER_TEXT_GREEN << F("Initializing I2C Scan") << EndLine;
    I2CBus.scan();

    AgricosDevices_Init();

    logger << LOG_MASTER << LOGGER_TEXT_GREEN << F("Executing setup tasks") << EndLine;
    SetupTasksRegister.run();

    logger << LOG_MASTER << LOGGER_TEXT_GREEN << F("Executing sensors setup tasks") << EndLine;
    SensorsRegister.setup();

    logger << LOG_MASTER << LOGGER_TEXT_GREEN << F("Configuring CLI Interface") << EndLine;
    AgricosCli_Setup();

    if (!TimeProvider)
    {
        throw_error(AGRICOS_ERROR_TIME_PROVIDER_NOT_DEFINED);
    }

    if (!AgricosCore_OutputTask)
    {
        throw_error(AGRICOS_ERROR_OUT_FUNCTION_NOT_DEFINED);
    }

    logger << LOG_MASTER << LOGGER_TEXT_GREEN << F("Executing loop...") << EndLine;
    while (1)
    {
        AgricosCore_Task();
    }
}

static char datetime[30];

static void AgricosCore_UpdateDateTime(void)
{
    TimeProvider->update();
    Time_s time = TimeProvider->getTime();
    time.toCharArray(datetime);
    // logger.setPrefix(datetime);
}

static bool AgricosCore_SendDataTrigger(void)
{
    Time_s time = TimeProvider->getTime();
    switch (Agricos_rtcMode)
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

static void AgricosCore_UpdateStatus()
{
    uint32_t millisecond = millis();
    while (millis() - millisecond > 5000)
    {
        if (millis() < millisecond)
        {
            millisecond = millis();
        }
        AgricosCore_UpdateDateTime();
    }
}

void AgricosCore_Task(void)
{
#if ENABLE_STATUS_LED
    if (last_blink > millis())
    {
        last_blink = millis();
    }
    if (millis() - last_blink > 500U)
    {
        StatusLed::blink();
        last_blink = millis();
    }
#endif
    AgricosCore_UpdateStatus();

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
            Agricos_SuccessMeasures++;
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

        Agricos_noMeasures++;
    }
    else if (!send)
    {
        Agricos_isSended = false;
    }
}