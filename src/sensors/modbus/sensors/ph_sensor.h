#if !defined(SENSORS_MODBUS_SENSORS_PH_H)
#define SENSORS_MODBUS_SENSORS_PH_H

#include "../base_sensor.h"

#define MODBUS_SENSOR_PH_REG_VALUE 0x0000

class ModbusPhSensor : public ModbusBaseSensor<1>
{
public:
    ModbusPhSensor(const char *name, HardwareSerial &port, uint8_t controlPin)
        : ModbusBaseSensor(name, port, controlPin,
                           (const VariableType_e[1]){
                               VARIABLE_TYPE_PH})
    {
    }

    void update() override
    {
        uint16_t ph = this->readRegister(MODBUS_SENSOR_PH_REG_VALUE);
        this->setMeasureValue<VARIABLE_TYPE_PH>(ph);
    }
};

#endif  // SENSORS_MODBUS_SENSORS_PH_H
