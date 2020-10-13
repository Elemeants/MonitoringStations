#include <Arduino.h>
#include <agricos/core.h>

void setup()
{
    AgricosCore_OutputTask = []() -> void { };
    AgricosCore_Init();
}

void loop()
{
}