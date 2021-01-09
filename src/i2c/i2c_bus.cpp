#include "i2c_bus.h"

#include "i2c_port.h"

extern IKernelLogger &logger;

void _I2CBus::begin()
{
    port.begin();
    logger.log(F("     └-- I2C bus begined"), LOG_INFO);
    for (int i = 0; i < devices.size(); i++)
    {
        I2CDevice *device = devices[i];
        if (device->isConnected())
        {
            if (!device->begin(device->address()))
            {
                logger << LOG_ERROR << F("      ~ Can't begin addrs: 0x") << String(device->address(), HEX) << EndLine;
            }
            else
            {
                logger << LOG_INFO << F("      + Device beginned on 0x") << String(device->address(), HEX) << EndLine;
            }
        }
        else
        {
            logger << LOG_ERROR << F("      ~ Device not connected addr: 0X") << String(device->address(), HEX) << EndLine;
        }
    }
}

void _I2CBus::scan()
{
    char buffer[3];
    port.begin();
    I2CDevice test;
    test.setPort(this->port);
    logger << LOG_INFO << F("     └-- Scanning I2C Bus ") << EndLine;
    logger << LOG_INFO << F("    ");

    for (size_t i = 1; i < 127; i++)
    {
        test.setAddress(i);

        if (test.isConnected())
        {
            sprintf(buffer, "%02X", i);
        }
        else
        {
            sprintf(buffer, "--");
        }

        logger << buffer << F(" ");

        if (i % 16 == 0)
        {
            logger << EndLine << LOG_INFO << F("    ");
        }
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