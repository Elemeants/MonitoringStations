#if !defined(DEVICES_STATUS_LED_DRIVER_H)
#define DEVICES_STATUS_LED_DRIVER_H

#define LED_GPIO_PIN 23

namespace StatusLed
{
void initLed();
void blink();
}  // namespace StatusLed

#endif  // DEVICES_STATUS_LED_DRIVER_H
