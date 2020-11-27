#if !defined(SENSORS_MODBUS_BUS_H)
#define SENSORS_MODBUS_BUS_H

#include "../sensors/leaf_sensor.h"
#include "../sensors/ph_sensor.h"
#include "../sensors/soil_sensor.h"

class ModbusSensorBus
{
public:
    void init();
    void updateAll();
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}


#endif  // SENSORS_MODBUS_BUS_H
