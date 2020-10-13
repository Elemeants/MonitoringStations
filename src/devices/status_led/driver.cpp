#include "driver.h"

#include <Arduino.h>

void StatusLed::initLed()
{
    pinMode(LED_GPIO_PIN, OUTPUT);
    digitalWrite(LED_GPIO_PIN, LOW);
}

void StatusLed::blink()
{
    digitalWrite(LED_GPIO_PIN, !digitalRead(LED_GPIO_PIN));
}
