#if !defined(__AGRICOS_BOARDS_V210_H)
#define __AGRICOS_BOARDS_V210_H

/**============================[ RTC Configuration ]============================*/

// RTC Model connected to the board
#define RTC_MODEL RTC_USE_DS3231

/**==========================[ MicroSD Configuration ]==========================*/

// MicroSD CS Pin
#define SD_CS_PIN 31

/**=========================[ Status Led Configuration ]========================*/

#define ENABLE_STATUS_LED 1

#define STATUS_LED_GPIO 30

/**============================[ GPRS Configuration ]===========================*/

// GSM Fona808 Reset pin
#define GPRS_RESET_PIN 32

/**============================[ CLI Configuration ]============================*/

#define CLI_INTERFACE_SERIAL Serial

/**===========================[ Meter Configuration ]===========================*/

#define GSM_GPRS_SERIAL_PORT Serial2

/**==========================[ GSM/GPRS Configuration ]=========================*/

#define GSM_GPRS_SERIAL_PORT Serial2

/**===========================[ ModBus Configuration ]==========================*/

#define RS485_SERIAL_PORT Serial3

#define RS485_CTRL_PIN 30

/**============================[ ADC Configuration ]============================*/

#define ADC0_ENABLED 0
#define ADC1_ENABLED 0
#define ADC2_ENABLED 0
#define ADC3_ENABLED 0

#endif  // __AGRICOS_BOARDS_V210_H
