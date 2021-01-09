#include "../facade.h"

#if AGRICOS_STATION_TARGET == CROPFIELD_CUSTOM_STATION
void AgricosStations_AddModbusSensors(ModbusSensorBus &bus)
{
    bus.addSensor(MODBUS_SOIL_SENSOR, "Soil1", 0x01);
}
#endif