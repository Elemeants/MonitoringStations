#if !defined(AGRICOS_DEVICES_H)
#define AGRICOS_DEVICES_H

#include <devices/include.h>

#include "config.h"

extern ITimeProvider *TimeProvider;

// ============ Configuration for board version 2.10
#if BOARD_VERSION == 210

#define RTC_MODEL RTC_USE_DS3231
extern IAdcI2CDevice *ADC_Device0;
extern IAdcI2CDevice *ADC_Device1;
extern bool ADC_Device0_Connected();
extern bool ADC_Device1_Connected();
#define SD_CS_PIN 31

// ============ Configuration for board version 2.00
#elif BOARD_VERSION == 200

#define SD_CS_PIN 48

#endif

extern void AgricosDevices_Init(void);

#endif  // AGRICOS_DEVICES_H
