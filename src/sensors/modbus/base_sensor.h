#if !defined(SENSORS_MODBUS_BASE_SENSOR_H)
#define SENSORS_MODBUS_BASE_SENSOR_H

#include <types/isensor.h>

#include "cmd_builder.h"
#include "cmd_reader.h"
#include "parser.h"

#define MODBUS_RX_BUFFER_SIZE 32U
#define MODBUS_TX_BUFFER_SIZE 32U

template <size_t Nvars>
class ModbusBaseSensor : public ISensor<Nvars>
{
private:
    HardwareSerial &serialPort;
    uint8_t controlPin;

    uint8_t _id;
    uint8_t rx_buffer[MODBUS_RX_BUFFER_SIZE];
    uint8_t tx_buffer[MODBUS_TX_BUFFER_SIZE];

public:
    ModbusBaseSensor(
        const char *name,
        HardwareSerial &serialPort,
        uint8_t controlPin,
        const VariableType_e types[])
        : ISensor<Nvars>(name, types),
          serialPort(serialPort),
          controlPin(controlPin),
          _id(0)
    {
    }

    virtual void setup() override
    {
    }

    virtual void update() override
    {
    }

    uint16_t readRegister(uint16_t reg)
    {
        LinkedList<uint16_t> result = ModbusCommandBuilder(_id, reg)
                                          .asRead()
                                          .setRxBuffer(rx_buffer, MODBUS_RX_BUFFER_SIZE)
                                          .build(tx_buffer, MODBUS_TX_BUFFER_SIZE)
                                          .setConfig(&serialPort, controlPin)
                                          .setReader<ModbusSingleRegisterReader>()
                                          .execute();
        return (result.size() == 0) ? 0U : result[0];
    }

    void writeRegister(uint16_t reg, uint16_t value)
    {
        ModbusCommandBuilder(_id, reg)
            .asWrite()
            .addWriteData(value)
            .build(tx_buffer, MODBUS_TX_BUFFER_SIZE)
            .setConfig(&serialPort, controlPin)
            .execute();
    }

    LinkedList<uint16_t> readMultiRegister(uint16_t reg, uint16_t no_regs)
    {
        return ModbusCommandBuilder(_id, reg)
            .asRead()
            .setRegQuantity(no_regs)
            .setRxBuffer(rx_buffer, MODBUS_RX_BUFFER_SIZE)
            .build(tx_buffer, MODBUS_TX_BUFFER_SIZE)
            .setConfig(&serialPort, controlPin)
            .setReader<ModbusMultiRegisterReader>()
            .execute();
    }

    void writeMultiRegister(uint16_t reg, uint16_t no_regs, uint8_t *buffer, uint8_t length)
    {
    }

    uint8_t id() const { return _id; }
    void setId(uint8_t id) { _id = id; }
};

#endif  // SENSORS_MODBUS_BASE_SENSOR_H
