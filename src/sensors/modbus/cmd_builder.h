#if !defined(SENSORS_MODBUS_COMMAND_BUILDER_H)
#define SENSORS_MODBUS_COMMAND_BUILDER_H

#include "cmd_sender.h"
#include "common.h"
#include "function_codes.h"

class ModbusCommandBuilder
{
private:
    uint8_t id;
    ModbusFunctionCode_e code;
    uint16_t addressReg;
    uint16_t quantityRegs;

    LinkedList<uint16_t> addressData;

    uint8_t *rx_buffer;
    uint8_t rx_length;

public:
    ModbusCommandBuilder(uint8_t id, uint8_t startReg)
        : id(id),
          code(MODBUS_FUNCTION_READ),
          addressReg(startReg),
          quantityRegs(1U),
          rx_buffer(NULL),
          rx_length(0)
    {
    }

    ModbusCommandBuilder &asWrite();
    ModbusCommandBuilder &asRead();

    ModbusCommandBuilder &setRegQuantity(uint8_t quantity);

    ModbusCommandBuilder &addWriteData(uint16_t _data);

    ModbusCommandBuilder &setRxBuffer(uint8_t *rx_buffer, uint8_t length);

    ModbusCommandSender build(uint8_t *buffer, uint16_t len);
};

#endif  // SENSORS_MODBUS_COMMAND_BUILDER_H
