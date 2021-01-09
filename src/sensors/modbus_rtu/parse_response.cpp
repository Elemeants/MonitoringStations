#include "parse_response.h"

uint16_t ParseSingleRegisterCommand(uint8_t *rx_buffer, uint8_t rx_len)
{
    // Avoid buffer out index overflow if length is less than 5 bytes
    // which is the minimum length allowed
    if (rx_len <= 5)
    {
        return 0x0000;
    }

    LinkedList<uint16_t> result;
    uint8_t _id = rx_buffer[0];
    uint8_t _code = rx_buffer[1];
    uint8_t _no_of_bytes = rx_buffer[2];
    const uint8_t DATA_OFFSET = 3;

    uint16_t value = rx_buffer[DATA_OFFSET] << 8 | rx_buffer[DATA_OFFSET + 1];

    const uint8_t CRC_OFFSET = DATA_OFFSET + _no_of_bytes;
    uint16_t crc = rx_buffer[CRC_OFFSET] | rx_buffer[CRC_OFFSET + 1] << 8;

    return value;
}

LinkedList<uint16_t> ParseMultiRegisterCommand(uint8_t *rx_buffer, uint8_t rx_len)
{
    LinkedList<uint16_t> result;
    // Avoid buffer out index overflow if length is less than 5 bytes
    // which is the minimum length allowed
    if (rx_len <= 5)
    {
        return result;
    }

    uint8_t _id = rx_buffer[0];
    uint8_t _code = rx_buffer[1];
    uint8_t _no_of_bytes = rx_buffer[2];

    const uint8_t DATA_OFFSET = 3;
    for (uint8_t i = 0; i < _no_of_bytes; i += 2)
    {
        uint16_t v = rx_buffer[DATA_OFFSET + i] << 8 | rx_buffer[DATA_OFFSET + i + 1];
        result.add(v);
    }
    const uint8_t CRC_OFFSET = DATA_OFFSET + _no_of_bytes;
    uint16_t crc = rx_buffer[CRC_OFFSET] | rx_buffer[CRC_OFFSET + 1] << 8;
    return result;
}