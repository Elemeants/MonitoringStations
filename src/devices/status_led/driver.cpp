#include "driver.h"

#include <Arduino.h>

static uint8_t LED_GPIO_PIN = 0;

void StatusLed::initLed(uint8_t pin)
{
    LED_GPIO_PIN = pin;
    pinMode(LED_GPIO_PIN, OUTPUT);
    digitalWrite(LED_GPIO_PIN, LOW);
}

void StatusLed::blink()
{
    digitalWrite(LED_GPIO_PIN, !digitalRead(LED_GPIO_PIN));
}
