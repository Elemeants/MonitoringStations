#include "rtc_mode_str.h"

const __FlashStringHelper* GetStringRtcMode(RTCMode_e mode)
{
    switch (mode)
    {
    case RTC_OFF:
        return F("OFF");
    case RTC_2_MINUTES:
        return F("2 min");
    case RTC_15_MINUTES:
        return F("15 min");
    case RTC_30_MINUTES:
        return F("30 min");
    default:
        return F("");
    }
}