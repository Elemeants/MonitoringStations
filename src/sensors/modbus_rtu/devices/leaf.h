#if !defined(__SENSORS_MODBUS_RTU_SENSORS_LEAF_H)
#define __SENSORS_MODBUS_RTU_SENSORS_LEAF_H

#include "../modbus_sensor.h"

#define MODBUS_SENSOR_LEAF_REG_VALUE 0x0000

class ModbusLeafSensor : public ModbusSensor
{
    uint16_t lastMeasure;

public:
    ModbusLeafSensor(const char *name, uint8_t id, ModbusRTULayer &layer)
        : ModbusSensor(name, id, layer,
                       (const VariableType_e[2]){VARIABLE_TYPE_LEAF_HUMIDITY,
                                                 VARIABLE_TYPE_LEAF_TEMPERATURE},
                       2)
    {
    }

    void update() override
    {
        LinkedList<uint16_t> measures = readMultiRegister(MODBUS_SENSOR_LEAF_REG_VALUE, 2U);
        this->setMeasureValue<VARIABLE_TYPE_LEAF_HUMIDITY>(measures[0]);
        this->setMeasureValue<VARIABLE_TYPE_LEAF_TEMPERATURE>(measures[1]);
    }
};

#endif  // __SENSORS_MODBUS_RTU_SENSORS_LEAF_H
