#if !defined(DEVICES_RTC_INCLUDE_H)
#define DEVICES_RTC_INCLUDE_H

#include "device_interface.h"
#include "ds3231.h"

#define RTC_USE_DS3231 1

void RTC_Setup(IRTCI2c &rtc);

#endif  // DEVICES_RTC_INCLUDE_H
