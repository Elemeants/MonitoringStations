#include <Arduino.h>
#include <agricos/core.h>

void setup()
{
    AgricosCore_OutputTask = []() -> bool {
        gprs_post_to_host();
        return true;
    };
    AgricosCore_Init();
}

void loop()
{
}