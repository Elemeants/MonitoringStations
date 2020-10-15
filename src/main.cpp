#include <Arduino.h>
#include <agricos/core.h>

void setup()
{
    AgricosCore_OutputTask = []() -> bool { return true; };
    AgricosCore_Init();
}

void loop()
{
}