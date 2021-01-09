#if !defined(SENSORS_MODBUS_BUS_H)
#define SENSORS_MODBUS_BUS_H

#include "../modbus_sensor.h"
#include "leaf.h"
#include "ph.h"
#include "soil.h"
#include "utils/linked_list.h"

typedef enum
{
    MODBUS_PH_SENSOR,
    MODBUS_SOIL_SENSOR,
    MODBUS_LEAF_SENSOR
} ModbusSensor_e;

class ModbusSensorBus
{
    LinkedList<ModbusSensor *> sensors;
    ModbusRTULayer &layer;

public:
    ModbusSensorBus(ModbusRTULayer &layer) : layer(layer) {}

    void init();
    void updateAll();

    void addSensor(ModbusSensor_e type, const char *name, uint8_t id);

    LinkedList<ModbusSensor *> *dumpSensorList();
};

#endif  // SENSORS_MODBUS_BUS_H
