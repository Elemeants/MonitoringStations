#include "include.h"

#define __TEST_PARAM_LED_BLINK_NUM 10
#define __TEST_PARAM_LED_BLINK_DELAY_MS 100

void AgricosCli_CMD_Test_Led()
{
    logger  << LOG_MASTER
            << LOGGER_TEXT_GREEN
            << F(" Blinking status led every ") 
            << __TEST_PARAM_LED_BLINK_DELAY_MS 
            << F("ms for ")
            << __TEST_PARAM_LED_BLINK_NUM
            << F(" times... ")
            << EndLine;
    for_in_range(uint8_t, i, 0, __TEST_PARAM_LED_BLINK_NUM)
    {
        StatusLed::blink();
        delay(__TEST_PARAM_LED_BLINK_DELAY_MS);
    }
    logger << LOG_MASTER << LOGGER_TEXT_YELLOW << F(" END TEST") << EndLine;
}