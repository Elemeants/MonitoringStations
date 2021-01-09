#include "include.h"

#include "common.h"

void RTC_Setup(IRTCI2c &rtc)
{
    I2CBus.add(&rtc);

    if (rtc.isConnected())
    {
        if (!rtc.begin(rtc.address()))
        {
            logger.log(F("          └-- Unable to begin to RTC"), LOG_ERROR);
        }
        else
        {
            logger.log(F("          └-- RTC: OK"), LOG_MASTER);
            rtc.update();
        }
    }
    else
    {
        logger.log(F("          └-- Unable to connect to RTC"), LOG_ERROR);
    }
}