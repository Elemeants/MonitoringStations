#if !defined(SENSOR_MODBUS_PASER_H)
#define SENSOR_MODBUS_PASER_H

#include "cmd_reader.h"

class ModbusSingleRegisterReader : public IModbusCommandReader
{
public:
    LinkedList<uint16_t> parse(uint8_t *buffer, uint8_t length)
    {
        LinkedList<uint16_t> result;
        uint8_t _id = buffer[0];
        uint8_t _code = buffer[1];
        uint8_t _no_of_bytes = buffer[2];
        const uint8_t DATA_OFFSET = 3;

        result.add(buffer[DATA_OFFSET] << 8 | buffer[DATA_OFFSET + 1]);

        const uint8_t CRC_OFFSET = DATA_OFFSET + _no_of_bytes;
        uint16_t crc = buffer[CRC_OFFSET] | buffer[CRC_OFFSET + 1] << 8;
        return result;
    }
};

class ModbusMultiRegisterReader : public IModbusCommandReader
{
public:
    LinkedList<uint16_t> parse(uint8_t *buffer, uint8_t length)
    {
        LinkedList<uint16_t> result;
        uint8_t _id = buffer[0];
        uint8_t _code = buffer[1];
        uint8_t _no_of_bytes = buffer[2];
        const uint8_t DATA_OFFSET = 3;
        for (uint8_t i = 0; i < _no_of_bytes; i += 2)
        {
            uint16_t v = buffer[DATA_OFFSET + i] << 8 | buffer[DATA_OFFSET + i + 1];
            result.add(v);
        }
        const uint8_t CRC_OFFSET = DATA_OFFSET + _no_of_bytes;
        uint16_t crc = buffer[CRC_OFFSET] | buffer[CRC_OFFSET + 1] << 8;
        return result;
    }
};

#endif  // SENSOR_MODBUS_PASER_H
