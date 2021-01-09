#if !defined(SENSORS_MODBUS_SENSORS_PH_H)
#define SENSORS_MODBUS_SENSORS_PH_H

#include "../modbus_sensor.h"

#define MODBUS_SENSOR_PH_REG_VALUE 0x0000

class ModbusPhSensor : public ModbusSensor
{
public:
    ModbusPhSensor(const char *name, uint8_t id, ModbusRTULayer &layer)
        : ModbusSensor(name, id, layer,
                       (const VariableType_e[1]){
                           VARIABLE_TYPE_PH},
                       1)
    {
    }

    void update() override
    {
        uint16_t ph = this->readRegister(MODBUS_SENSOR_PH_REG_VALUE);
        this->setMeasureValue<VARIABLE_TYPE_PH>(ph);
    }
};

#endif  // SENSORS_MODBUS_SENSORS_PH_H
