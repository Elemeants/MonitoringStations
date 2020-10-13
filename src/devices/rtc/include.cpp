#include "include.h"

#include "common.h"

void RTC_Setup(IRTCI2c &rtc)
{
    I2CBus.add(&rtc);

    if (rtc.isConnected())
    {
        if (!rtc.begin(rtc.address()))
        {
            logger.log(F("          └── Unable to begin to RTC"), LOG_ERROR);
        }
        else
        {
            logger.log(F("          └── RTC: OK"), LOG_MASTER);
        }
#if ADJUST_RTC_FROM_COMPILER
        else
        {
            logger.log(F("    Adjusting time RTC"), LOG_MASTER);
            rtc.adjustRtc(__DATE__, "15:50:02");
        }
#endif
    }
    else
    {
        logger.log(F("          └── Unable to connect to RTC"), LOG_ERROR);
    }
}