#include "i2c_port.h"

#if USE_FREERTOS_I2C
SemaphoreHandle_t TwoWireRTOS::xI2CSemaphore = NULL;

TwoWireRTOS::TwoWireRTOS()
    : TwoWire(0)
{
    if (xI2CSemaphore == NULL)
    {
        xI2CSemaphore = xSemaphoreCreateMutex();
        if (xI2CSemaphore != NULL)
        {
            xSemaphoreGive(xI2CSemaphore);
        }
    }
}

bool TwoWireRTOS::lockWire()
{
    return (xSemaphoreTake(xI2CSemaphore, portMAX_DELAY) == pdPASS);
}

void TwoWireRTOS::unlockWire()
{
    xSemaphoreGive(xI2CSemaphore);
}
TwoWireRTOS KernelWire;
#else
TwoWire KernelWire;
#endif
