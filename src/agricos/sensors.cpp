#include "sensors.h"

#include "devices.h"
#include "stations/facade.h"

LinkedList<SensorInfo_t *> StationSensors;

static ModbusRTULayer ModbusTransportLayer(RS485_SERIAL_PORT, RS485_CTRL_PIN);
static ModbusSensorBus ModbusController(ModbusTransportLayer);

static void AgricosSensors_ModbusInit()
{
    logger << LOG_MASTER << F("    ├-- Adding Modbus sensors") << EndLine;
    AgricosStations_AddModbusSensors(ModbusController);
    LinkedList<ModbusSensor *> *list = ModbusController.dumpSensorList();
    for_in_range(auto, i, 0, list->size())
    {
        SensorInfo_t *info = &list->get(i)->getInfo();
        StationSensors.add(info);
    }
    ModbusController.init();
}

void AgricosSensors_Init()
{
    logger << LOG_MASTER << LOGGER_TEXT_YELLOW << F("Initializing Sensors [")
           << LOGGER_TEXT_GREEN << F(AGRICOS_STATION_TARGET_STR) << LOGGER_TEXT_YELLOW << F("]") << EndLine;
    AgricosSensors_ModbusInit();
}

void AgricosSensors_Update()
{
    ModbusController.updateAll();
}