#include "../facade.h"

#if AGRICOS_STATION_TARGET == CROPFIELD_POMAS_ES003
void AgricosStations_AddModbusSensors(ModbusSensorBus &bus)
{
    bus.addSensor(MODBUS_SOIL_SENSOR, "Soil1", 0x01);
    bus.addSensor(MODBUS_SOIL_SENSOR, "Soil2", 0x02);
    bus.addSensor(MODBUS_SOIL_SENSOR, "Soil3", 0x03);
    bus.addSensor(MODBUS_SOIL_SENSOR, "Soil4", 0x04);
    bus.addSensor(MODBUS_SOIL_SENSOR, "Soil5", 0x05);

    bus.addSensor(MODBUS_PH_SENSOR, "pH1", 0x11);
    bus.addSensor(MODBUS_PH_SENSOR, "pH2", 0x12);
    bus.addSensor(MODBUS_PH_SENSOR, "pH3", 0x13);
    bus.addSensor(MODBUS_PH_SENSOR, "pH4", 0x14);
    bus.addSensor(MODBUS_PH_SENSOR, "pH5", 0x15);
}
#endif