#include "i2c_bus.h"

#include "i2c_port.h"

extern IKernelLogger &logger;

void _I2CBus::begin()
{
    port.begin();
    logger.log(F("     └-- Beginning I2C Bus"), LOG_INFO);
    logger << INT_HEX;

    for (int i = 0; i < devices.size(); i++)
    {
        I2CDevice *device = devices[i];

        logger << LOG_INFO << F("          └-- Device on 0x") << device->address() << F(" # ");
        if (device->isConnected())
        {
            if (!device->begin(device->address()))
            {
                logger << LOGGER_TEXT_RED << F("ERROR (Begin)");
            }
            else
            {
                logger << LOGGER_TEXT_GREEN << F("OK");
            }
        }
        else
        {
            logger << LOGGER_TEXT_RED << F("ERROR (Connection)");
        }
        logger << EndLine;
    }
}

void _I2CBus::scan()
{
    uint8_t row = 0;
    char buffer[3];
    port.begin();
    I2CDevice test;
    test.setPort(this->port);
    logger << LOG_INFO << F("     └-- Scanning I2C Bus ") << EndLine;
    logger << LOG_INFO << F("         0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F") << EndLine;
    logger << LOG_INFO << F("    00: -- ");

    for (size_t i = 1; i < 0x80; i++)
    {
        test.setAddress(i);
    
        if (i % 16 == 0)
        {
            row += 0x10;
            sprintf(buffer, "%02X", row);
            logger << EndLine << LOG_INFO << F("    ") << buffer << F(": ");
        }

        if (test.isConnected())
        {
            sprintf(buffer, "%02X", i);
        }
        else
        {
            sprintf(buffer, "--");
        }

        logger << buffer << F(" ");

    }
    logger << EndLine;
}

_I2CBus &_I2CBus::add(I2CDevice *_device)
{
    _device->setPort(this->port);
    devices.add(_device);
    return *this;
}

_I2CBus I2CBus(KernelWire);