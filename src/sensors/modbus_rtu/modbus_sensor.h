#if !defined(__SENSORS_MODBUS_RTU_MODBUS_SENSOR_H)
#define __SENSORS_MODBUS_RTU_MODBUS_SENSOR_H

#include "command_builder.h"
#include "parse_response.h"
#include "transport_layer.h"
#include "types/isensor.h"
#include "types/sensor_protocols.h"

#define MODBUS_SENSOR_BUFFER_SIZE 32

class ModbusSensor : public ISensor
{
private:
    ModbusRTULayer &layer;
    uint8_t deviceId;

    uint8_t tx_buffer[MODBUS_SENSOR_BUFFER_SIZE];
    uint8_t rx_buffer[MODBUS_SENSOR_BUFFER_SIZE];

    uint8_t rx_length;
    uint8_t tx_length;

public:
    ModbusSensor(
        const char *name,
        uint8_t deviceId,
        ModbusRTULayer &layer,
        const VariableType_e vars[],
        uint8_t vars_len)
        : ISensor(name, SENSOR_PROTOCOL_MODBUS, vars, vars_len),
          layer(layer),
          deviceId(deviceId),
          rx_length(MODBUS_SENSOR_BUFFER_SIZE),
          tx_length(MODBUS_SENSOR_BUFFER_SIZE)
    {
    }

    virtual void setup() override { }

    virtual void update() override { }

    uint16_t readRegister(uint16_t reg);

    void writeRegister(uint16_t reg, uint16_t value);

    LinkedList<uint16_t> readMultiRegister(uint16_t reg, uint16_t no_regs);
};

#endif  // __SENSORS_MODBUS_RTU_MODBUS_SENSOR_H
