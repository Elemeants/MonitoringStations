#include "include.h"

#include "common.h"

void RTC_Setup(IRTCI2c &rtc)
{
    I2CBus.add(&rtc);

    logger << LOG_MASTER << F("          └-- RTC Setup: ");
    if (rtc.isConnected())
    {
        if (!rtc.begin(rtc.address()))
        {
            logger << LOGGER_TEXT_RED << F("ERROR (Begin)");
        }
        else
        {
            logger << LOGGER_TEXT_GREEN << F("OK");
            rtc.update();
        }
    }
    else
    {
        logger << LOGGER_TEXT_RED << F("ERROR (Connection)");
    }
    logger << EndLine;
}