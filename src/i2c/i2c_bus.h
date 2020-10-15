/**
 * @file i2c_bus.h
 * @author Daniel Polanco (jpolanco@getinsoft.com)
 * @brief I2CBus manager class
 * @version 1.0
 * @date 2020-01-07
 * 
 */
#ifndef I2C_BUS_H
#define I2C_BUS_H

#include <Wire.h>
#include <stdint.h>

#include "i2c_device.h"
#include "logger/ikernel_logger.h"
#include "utils/linked_list.h"

/**
 * @brief I2C bus manager
 * @details Provides an API to manage devices in an I2C port
 * 
 */
class _I2CBus
{
private:
    /**
   * @brief [Private Attribute] I2C port reference
   * 
   */
    TwoWire &port;

    /**
   * @brief [Private Attribute] Linked list of interface pointers
   *        of the devices attached to the bus
   * 
   */
    LinkedList<I2CDevice *> devices;

public:
    /**
   * @brief Construct a new I2CBus
   * 
   * @param port I2C Port
   */
    _I2CBus(TwoWire &port) : port(port) {}

    /**
   * @brief [Public Method] Begins the bus and all devices connected
   * 
   */
    void begin();

    /**
   * @brief [Public Method] Adds a device to the bus
   * 
   * @param _device 
   * @return I2CBus& 
   */
    _I2CBus &add(I2CDevice *_device);

    void scan();
    /**
   * @brief [Getter] Gets a pointer to the device connected in the address
   * 
   * @tparam T Type of i2c device
   * @param addrss Address of the device
   * @return T* Casted pointer to the i2c device to allow polymorphism
   */
    template <typename T>
    T *get(uint8_t addrss);
};

/////////////////////////////////////////////////////////////////
// Class template implementation
/////////////////////////////////////////////////////////////////
template <typename T>
T *_I2CBus::get(uint8_t addrss)
{
    for (int i = 0; i < devices.size(); i++)
    {
        I2CDevice *device = devices[i];
        if (device->address() == addrss)
        {
            return (T *)(device);
        }
    }
    logger << LOG_ERROR << F("Do not exists an device with address: 0x") << INT_HEX << addrss << EndLine;
    return NULL;
}

extern _I2CBus I2CBus;

#endif  // !I2C_BUS_H