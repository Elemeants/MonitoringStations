#if !defined(DEVICES_ADC_SETUP_H)
#define DEVICES_ADC_SETUP_H

#include "device.h"
#include "i2c_adc.h"
#include "modules/ads1115.h"

void ADC_Init(IAdcI2CDevice *devices[], uint8_t lenght);

#endif  // DEVICES_ADC_SETUP_H
