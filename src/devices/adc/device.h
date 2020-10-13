#if !defined(DEVICES_ADC_DEVICE_H)
#define DEVICES_ADC_DEVICE_H

#include <stdint.h>

class IAdcDevice
{
public:
    virtual uint16_t read(uint8_t channel) = 0;
    virtual uint16_t readDiff(uint8_t mode) = 0;
};

#endif  // DEVICES_ADC_DEVICE_H
