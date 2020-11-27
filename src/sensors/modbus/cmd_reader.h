#if !defined(SENSORS_MODBUS_COMMAND_READER_H)
#define SENSORS_MODBUS_COMMAND_READER_H

#include "common.h"

class IModbusCommandReader
{
public:
    virtual LinkedList<uint16_t> parse(uint8_t* buffer, uint8_t length) = 0;
};

#endif  // SENSORS_MODBUS_COMMAND_READER_H
