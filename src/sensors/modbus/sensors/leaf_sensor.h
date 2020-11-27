#if !defined(SENSORS_MODBUS_SENSORS_LEAF_H)
#define SENSORS_MODBUS_SENSORS_LEAF_H

#include "../base_sensor.h"

#define MODBUS_SENSOR_LEAF_REG_VALUE 0x0000

class ModbusLeafSensor : public ModbusBaseSensor<2>
{
public:
    ModbusLeafSensor(const char *name, HardwareSerial &port, uint8_t controlPin)
        : ModbusBaseSensor(name, port, controlPin,
                           (const VariableType_e[2]){
                               VARIABLE_TYPE_LEAF_HUMIDITY,
                               VARIABLE_TYPE_LEAF_TEMPERATURE})
    {
    }

    void update() override
    {
        LinkedList<uint16_t> measures = this->readMultiRegister(MODBUS_SENSOR_LEAF_REG_VALUE, 2U);
        this->setMeasureValue<VARIABLE_TYPE_LEAF_HUMIDITY>(measures[0]);
        this->setMeasureValue<VARIABLE_TYPE_LEAF_TEMPERATURE>(measures[1]);
    }
};

#endif  // SENSORS_MODBUS_SENSORS_LEAF_H
