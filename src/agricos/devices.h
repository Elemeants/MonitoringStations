#if !defined(AGRICOS_DEVICES_H)
#define AGRICOS_DEVICES_H

#include <devices/include.h>

#include "config.h"
#include "board.h"

extern ITimeProvider *TimeProvider;

#define RTC_MODEL RTC_USE_DS3231

extern void AgricosDevices_ADC_Connected(uint8_t id);
extern void AgricosDevices_Init(void);

#endif  // AGRICOS_DEVICES_H
