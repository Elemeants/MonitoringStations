#include "devices.h"

#include "globals.h"

#if BOARD_VERSION == 210
static ADS1115 adc_0 = ADS1115(ADS1115_IIC_ADDRESS1);
IAdcI2CDevice *ADC_Device0 = &adc_0;
static ADS1115 adc_1 = ADS1115(ADS1115_IIC_ADDRESS3);
IAdcI2CDevice *ADC_Device1 = &adc_1;

bool ADC_Device0_Connected()
{
    return adc_0.isConnected();
}

bool ADC_Device1_Connected()
{
    return adc_1.isConnected();
}

#endif

#if RTC_MODEL == RTC_USE_DS3231
static DS3231 _rtc;
#endif

ITimeProvider *TimeProvider = &_rtc;

IAdcI2CDevice *ADC_Devices[] = {
    ADC_Device0,
    ADC_Device1};

void AgricosDevices_Init(void)
{
    logger << LOG_MASTER << LOGGER_TEXT_GREEN << F("Initializing Devices") << EndLine;

    logger << LOG_MASTER << F("    ├── Initializing Drivers - RTC") << EndLine;
    RTC_Setup(_rtc);

    logger << LOG_INFO << F("    ├── Initializing GSM device") << EndLine;
    GSM_Init();

    logger << LOG_INFO << F("    ├── Initializing GPRS") << EndLine;
    GSM_GPRSInit();
    // GSM_PrintStatus();

    logger << LOG_MASTER << F("    ├── Initializing Drivers - ACD") << EndLine;
    ADC_Init(ADC_Devices, array_size(ADC_Devices));

    logger << LOG_MASTER << F("    └── Initializing Status Led") << EndLine;
    StatusLed::initLed(STATUS_LED_GPIO);
}