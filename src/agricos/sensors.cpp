#include "sensors.h"

#include "devices.h"

#if BOARD_VERSION == 210
void AgricosSensors_Init()
{
    if (ADC_Device0_Connected())
    {
    }
}
#endif