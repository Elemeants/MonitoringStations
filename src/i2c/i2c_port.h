#ifndef KERNEL_I2C_PORT_H
#define KERNEL_I2C_PORT_H

#include <Wire.h>
#include <Arduino.h>

#include "config.h"

#if USE_FREERTOS_I2C
/**
 * @brief I2C Port compatible with rtos
 * @details Provides additional methods to control the i2c bus flow
 *          uses an static semaphore to allow writing to the port
 * 
 */
class TwoWireRTOS : public TwoWire
{
private:
    /**
   * @brief [Static Private Attribute] Static resource binary semaphore 
   * 
   */
    static SemaphoreHandle_t xI2CSemaphore;

public:
    /**
   * @brief Construct a new TwoWireRTOS
   * 
   */
    TwoWireRTOS();

    /**
   * @brief [Public Method] Locks the wire flow
   * @details Try to lock the wire if is busy, awaits until the port get free to use
   * 
   * @return bool Is is success the lock of the port
   */
    bool lockWire();

    /**
   * @brief [Public Method] Unlocks the wire flow
   * @details Release the port for other tasks
   * 
   */
    void unlockWire();
};
/**
 * @brief Global instance of TwoWireRTOS
 * 
 */
extern TwoWireRTOS KernelWire;
#else
extern TwoWire KernelWire;
#endif

#endif  // !KERNEL_I2C_PORT_H