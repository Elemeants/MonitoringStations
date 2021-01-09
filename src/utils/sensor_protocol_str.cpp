#include "sensor_protocol_str.h"

const __FlashStringHelper *SensorProtocolToStr(SensorProtocols_e protocol)
{
    switch (protocol)
    {
    case SENSOR_PROTOCOL_I2C:
        return F("I2C");
    case SENSOR_PROTOCOL_DDI:
        return F("DDI");
    case SENSOR_PROTOCOL_SPI:
        return F("SPI");
    case SENSOR_PROTOCOL_MODBUS:
        return F("MODBUS");
    case SENSOR_PROTOCOL_SERIAL:
        return F("SERIAL");
    case SENSOR_PROTOCOL_ANALOG:
        return F("ANALOG");
    default:
        return F("");
    }
}