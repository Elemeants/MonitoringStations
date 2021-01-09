#include "command_builder.h"

#include "utils/crc_16.h"
#include "utils/linked_list_utils.h"

ModbusCmdBuilderOps_t ModbusCmdFactory::CreateWriteCommand(uint8_t id, LinkedList<uint16_t> data, uint8_t quantity, uint8_t regAddress)
{
    return {id, MODBUS_FUNCTION_WRITE, regAddress, quantity, data};
}

ModbusCmdBuilderOps_t ModbusCmdFactory::CreateReadCommand(uint8_t id, uint8_t quantity, uint8_t regAddress)
{
    return {id, MODBUS_FUNCTION_READ, regAddress, quantity, LinkedList<uint16_t>()};
}

static inline void write16bit(uint8_t *buffer, uint16_t _data)
{
    buffer[0] = (_data & 0x00FF);
    buffer[1] = (_data & 0xFF00) >> 8;
}

void ModbusBuildCommand(ModbusCmdBuilderOps_t opts, uint8_t *buff, uint8_t *tx_length, uint8_t *rx_length)
{
    // Sets first 8 bytes (id, code, register_l, register_h, quantity_l, quantity_h, crc_l, crc_h)
    uint8_t calculated_length = 8;
    // If function code is write then add the byte of quantity and the words added
    if (opts.mode == MODBUS_FUNCTION_WRITE)
    {
        calculated_length += 1 + (opts.regData.size() * sizeof(uint16_t));
    }

    // Clear buffer to avoid errors on writing
    memset(buff, 0x00, *tx_length);

    // First byte will always be the id
    buff[0] = opts.id;
    // Second byte is function code (write: 0x06, read: 0x03)
    buff[1] = (uint8_t)opts.mode;

    // Uses an special function to write the values because the buffer must be in BigEndian order
    write16bit(&buff[2], opts.regAddress);
    write16bit(&buff[4], opts.numRegisters);

    if (opts.mode == MODBUS_FUNCTION_WRITE)
    {
        const uint8_t SIZE_INDEX_START = 6;
        const uint8_t WRITE_INDEX_START = SIZE_INDEX_START + 1;

        // Quantity of words
        buff[SIZE_INDEX_START] = opts.regData.size();

        // Fill buffer with the data
        for_in_range(uint8_t, i, 0, buff[6])
        {
            write16bit(&buff[WRITE_INDEX_START + (i * 2)], opts.regData[i]);
        }
    }

    // Calculate CRC of the package without the CRC spacing bytes
    uint16_t crc = calculate_crc16(buff, calculated_length - sizeof(uint16_t));

    write16bit(&buff[calculated_length - 2], crc);
    // buff[calculated_length - 1] = (crc & 0xFF00) >> 8;
    // buff[calculated_length - 2] = crc & 0x00FF;

    // Rx package lenght calculation
    // Start with the id byte and function code byte
    uint8_t rx_calculated_length = 2;

    switch (opts.mode)
    {
    case MODBUS_FUNCTION_READ:
        // (no_bytes, quantity_of_regs(words), crc_l, crc_h)
        rx_calculated_length += 1 + (opts.numRegisters * sizeof(uint16_t)) + 2;
    case MODBUS_FUNCTION_WRITE:
        // (Start addr, End addr, Quantity_h, Quantity_l, crc_l, crc_h)
        rx_calculated_length += 6;
    }
    
    *rx_length = rx_calculated_length;
    *tx_length = calculated_length;
}