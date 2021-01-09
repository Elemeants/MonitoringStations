#if !defined(SENSORS_MODBUS_SENSORS_SOIL_H)
#define SENSORS_MODBUS_SENSORS_SOIL_H

#include "../modbus_sensor.h"

#define MODBUS_SENSOR_LEAF_REG_VALUE 0x0000

class ModbusSoilSensor : public ModbusSensor
{
public:
    ModbusSoilSensor(const char *name, uint8_t id, ModbusRTULayer &layer)
        : ModbusSensor(name, id, layer,
                       (const VariableType_e[4]){
                           VARIABLE_TYPE_EC,
                           VARIABLE_TYPE_SOIL_HUMIDITY,
                           VARIABLE_TYPE_SOIL_TEMPERATURE,
                           VARIABLE_TYPE_SOIL_SALINITY},
                       4)
    {
    }

    void update() override
    {
        LinkedList<uint16_t> measures = this->readMultiRegister(MODBUS_SENSOR_LEAF_REG_VALUE, 4U);
        this->setMeasureValue<VARIABLE_TYPE_EC>(measures[0]);
        this->setMeasureValue<VARIABLE_TYPE_SOIL_HUMIDITY>(measures[1]);
        this->setMeasureValue<VARIABLE_TYPE_SOIL_TEMPERATURE>(measures[2]);
        this->setMeasureValue<VARIABLE_TYPE_SOIL_SALINITY>(measures[3]);
    }
};

#endif  // SENSORS_MODBUS_SENSORS_SOIL_H
