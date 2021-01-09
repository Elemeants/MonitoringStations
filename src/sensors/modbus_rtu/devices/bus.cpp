#include "bus.h"

void ModbusSensorBus::init()
{
    layer.init();
    for_in_range(auto, i, 0, sensors.size())
    {
        sensors.get(i)->setup();
    }
}

void ModbusSensorBus::updateAll()
{
    logger << LOG_INFO << F("     └-- Updating Modbus Sensors") << EndLine;
    for_in_range(auto, i, 0, sensors.size())
    {
        ModbusSensor *sensor = sensors.get(i);
        logger << LOG_INFO << F("           ├-- Sensor ID: ") << LOGGER_TEXT_YELLOW << sensor->getId() << EndLine;
        sensor->update();
    }
}

void ModbusSensorBus::addSensor(ModbusSensor_e type, const char *name, uint8_t id)
{
    ModbusSensor *sensor = NULL;
    switch (type)
    {
    case MODBUS_PH_SENSOR:
        sensor = new ModbusPhSensor(name, id, layer);
        break;

    case MODBUS_SOIL_SENSOR:
        sensor = new ModbusSoilSensor(name, id, layer);
        break;

    case MODBUS_LEAF_SENSOR:
        sensor = new ModbusLeafSensor(name, id, layer);
        break;

    default:
        break;
    }

    // Unknown sensor type - ERROR
    if (sensor == NULL)
    {
        return;
    }

    sensors.add(sensor);
}

LinkedList<ModbusSensor *> *ModbusSensorBus::dumpSensorList()
{
    return &sensors;
}