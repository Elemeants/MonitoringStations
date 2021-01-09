#if !defined(__RTC_MODE_TO_STRING_H)
#define __RTC_MODE_TO_STRING_H

#include <Arduino.h>
#include "types/rtc_mode.h"

extern const __FlashStringHelper* GetStringRtcMode(RTCMode_e mode);

#endif // __RTC_MODE_TO_STRING_H
