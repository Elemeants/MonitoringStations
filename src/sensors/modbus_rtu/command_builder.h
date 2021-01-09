#if !defined(__SENSORS_MODBUS_RTU_COMMAND_BUILDER_H)
#define __SENSORS_MODBUS_RTU_COMMAND_BUILDER_H

#include <Arduino.h>
#include "utils/linked_list.h"

typedef enum
{
    MODBUS_FUNCTION_READ = 0x03,
    MODBUS_FUNCTION_WRITE = 0x06
} ModbusFunctionCode_e;

typedef struct
{
    uint8_t id;
    ModbusFunctionCode_e mode;

    uint16_t regAddress;
    uint16_t numRegisters;

    LinkedList<uint16_t> regData;
} ModbusCmdBuilderOps_t;

class ModbusCmdFactory
{
public:
    static ModbusCmdBuilderOps_t CreateWriteCommand(uint8_t id, LinkedList<uint16_t> data, uint8_t quantity = 0x0001, uint8_t regAddress = 0x0000);
    static ModbusCmdBuilderOps_t CreateReadCommand(uint8_t id, uint8_t quantity = 0x0001, uint8_t regAddress = 0x0000);
};

void ModbusBuildCommand(ModbusCmdBuilderOps_t opts, uint8_t *buff, uint8_t *tx_length, uint8_t *rx_length);

#endif  // __SENSORS_MODBUS_RTU_COMMAND_BUILDER_H
