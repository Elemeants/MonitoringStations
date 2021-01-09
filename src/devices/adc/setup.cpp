#include "setup.h"

#include "common.h"

void ADC_Init(IAdcI2CDevice *devices[], uint8_t lenght)
{
    for_in_range(uint8_t, index, 0, lenght)
    {
        I2CBus.add(devices[index]);

        if (devices[index]->isConnected())
        {
            logger << LOG_MASTER << F("         ├-- ADC Device on 0x") << String(index, HEX) << F(": OK") << EndLine;
        }
        else
        {
            logger << LOG_ERROR << F("          ├-- ADC Device on 0x") << String(index, HEX) << F(": ERROR") << EndLine;
        }
    }
}
