#include "devices.h"

#include "config.h"
#include "globals.h"

#if ADC0_ENABLED
static ADS1115 adc_0 = ADS1115(ADS1115_IIC_ADDRESS0);
IAdcI2CDevice *ADC_Device0 = &adc_0;
#endif
#if ADC1_ENABLED
static ADS1115 adc_1 = ADS1115(ADS1115_IIC_ADDRESS1);
IAdcI2CDevice *ADC_Device1 = &adc_1;
#endif
#if ADC2_ENABLED
static ADS1115 adc_2 = ADS1115(ADS1115_IIC_ADDRESS2);
IAdcI2CDevice *ADC_Device2 = &adc_2;
#endif
#if ADC3_ENABLED
static ADS1115 adc_3 = ADS1115(ADS1115_IIC_ADDRESS3);
IAdcI2CDevice *ADC_Device3 = &adc_3;
#endif

#if RTC_MODEL == RTC_USE_DS3231
static DS3231 _rtc;
#endif

HardwareSerial &GSM_SerialPort = GSM_GPRS_SERIAL_PORT;
uint8_t GSM_ResetPin = GPRS_RESET_PIN;

ITimeProvider *TimeProvider = &_rtc;

IAdcI2CDevice *ADC_Devices[] = {
#if ADC0_ENABLED
    ADC_Device0,
#endif
#if ADC1_ENABLED
    ADC_Device1,
#endif
#if ADC2_ENABLED
    ADC_Device2,
#endif
#if ADC3_ENABLED
    ADC_Device3,
#endif
};

void AgricosDevices_Init(void)
{
    logger << LOG_MASTER << LOGGER_TEXT_YELLOW << F("Initializing Devices [")
           << LOGGER_TEXT_GREEN << F("Board ") << BOARD_VERSION << LOGGER_TEXT_YELLOW << F("]") << EndLine;

    logger << LOG_MASTER << F("    ├-- Initializing Drivers - RTC") << EndLine;
    RTC_Setup(_rtc);

    logger << LOG_INFO << F("    ├-- Initializing GSM device") << EndLine;
    if (GSM_Init())
    {
        logger << LOG_INFO << F("    ├-- Initializing GPRS") << EndLine;
        GSM_GPRSInit();

        logger << LOG_INFO << F("    ├-- GSM/GPRS Status") << EndLine;
        GSM_PrintStatus();
    }

    logger << LOG_MASTER << F("    ├-- Initializing Drivers - ACD") << EndLine;
    ADC_Init(ADC_Devices, array_size(ADC_Devices));

    logger << LOG_MASTER << F("    ├-- Initializing Drivers - MicroSD") << EndLine;
    MicroSD_Init(SD_CS_PIN);

    logger << LOG_MASTER << F("    └-- Initializing Status Led") << EndLine;
    StatusLed::initLed(STATUS_LED_GPIO);
}