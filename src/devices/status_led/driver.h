#if !defined(DEVICES_STATUS_LED_DRIVER_H)
#define DEVICES_STATUS_LED_DRIVER_H

#include <stdint.h>

namespace StatusLed
{
void initLed(uint8_t pin);
void blink();
}  // namespace StatusLed

#endif  // DEVICES_STATUS_LED_DRIVER_H
