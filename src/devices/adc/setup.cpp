#include "setup.h"

#include "common.h"

void ADC_Init(IAdcI2CDevice *devices[], uint8_t lenght)
{
    for_in_range(uint8_t, index, 0, lenght)
    {
        I2CBus.add(devices[index]);
        logger << LOG_MASTER << F("         ├-- ADC on Id 0x") << INT_HEX << devices[index]->address() << INT_DEC;

        if (devices[index]->isConnected())
        {
            logger << LOGGER_TEXT_GREEN << F(" # OK");
        }
        else
        {
            logger << LOGGER_TEXT_RED << F(" # Not connected");
        }
        logger << EndLine;
    }
}
