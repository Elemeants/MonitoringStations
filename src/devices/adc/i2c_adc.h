#if !defined(DEVICES_ADC_I2C_ADC_H)
#define DEVICES_ADC_I2C_ADC_H

#include "device.h"
#include "i2c/import.h"

class IAdcI2CDevice : public I2CDevice, public IAdcDevice
{
};

#endif  // DEVICES_ADC_I2C_ADC_H
