#include "cmd_builder.h"

ModbusCommandBuilder &ModbusCommandBuilder::asWrite()
{
    this->code = MODBUS_FUNCTION_WRITE;
    return *this;
}

ModbusCommandBuilder &ModbusCommandBuilder::asRead()
{
    this->code = MODBUS_FUNCTION_READ;
    return *this;
}

ModbusCommandBuilder &ModbusCommandBuilder::setRegQuantity(uint8_t quantity)
{
    this->quantityRegs = quantity;
    return *this;
}

ModbusCommandBuilder &ModbusCommandBuilder::addWriteData(uint16_t _data)
{
    this->addressData.add(_data);
    return *this;
}

ModbusCommandBuilder &ModbusCommandBuilder::setRxBuffer(uint8_t *rx_buffer, uint8_t length)
{
    this->rx_buffer = rx_buffer;
    this->rx_length = length;
    return *this;
}

static inline void write16bit(uint8_t *buffer, uint16_t _data)
{
    buffer[0] = (_data & 0x00FF);
    buffer[1] = (_data & 0xFF00) >> 8;
}

ModbusCommandSender ModbusCommandBuilder::build(uint8_t *buffer, uint16_t len)
{
    // Sets first 8 bytes (id, code, register_l, register_h, quantity_l, quantity_h, crc_l, crc_h)
    uint8_t calculated_length = 8;
    // If function code is write then add the byte of quantity and the words added
    if (code == MODBUS_FUNCTION_WRITE)
    {
        calculated_length += 1 + (this->addressData.size() * sizeof(uint16_t));
    }

    // Fill buffer with the command
    buffer[0] = this->id;
    buffer[1] = (uint8_t)this->code;
    write16bit(&buffer[2], this->addressReg);
    write16bit(&buffer[4], this->quantityRegs);

    if (code == MODBUS_FUNCTION_WRITE)
    {
        const uint8_t SIZE_INDEX_START = 6;
        const uint8_t WRITE_INDEX_START = SIZE_INDEX_START + 1;

        // Quantity of words
        buffer[SIZE_INDEX_START] = this->addressData.size();

        // Fill buffer with the data
        for_in_range(uint8_t, index, 0, buffer[6])
        {
            write16bit(&buffer[WRITE_INDEX_START + (index * 2)], this->addressData[index]);
        }
    }

    // Calculate CRC of the package without the CRC spacing bytes
    uint16_t crc = calculate_crc16(buffer, calculated_length - sizeof(uint16_t));
    buffer[calculated_length - 1] = (crc & 0xFF00) >> 8;
    buffer[calculated_length - 2] = crc & 0x00FF;

    // Rx package lenght calculation
    // Start with the id byte and function code byte
    uint8_t rx_calculated_length = 2;

    switch (code)
    {
    case MODBUS_FUNCTION_READ:
        // (no_bytes, quantity_of_regs(words), crc_l, crc_h)
        rx_calculated_length += 1 + (quantityRegs * sizeof(uint16_t)) + 2;
    case MODBUS_FUNCTION_WRITE:
        // (Start addr, End addr, Quantity_h, Quantity_l, crc_l, crc_h)
        rx_calculated_length += 6;
    }

    return ModbusCommandSender(buffer, calculated_length, rx_buffer, rx_calculated_length);
}