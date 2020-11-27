#if !defined(SENSORS_MODBUS_COMMAND_SENDER_H)
#define SENSORS_MODBUS_COMMAND_SENDER_H

#include "cmd_reader.h"
#include "common.h"

class ModbusCommandSender
{
    HardwareSerial *port;
    uint16_t delay_in_ms;
    uint8_t controlPin;
    IModbusCommandReader *reader;
    uint8_t max_attempts;

    const uint8_t *buffer_cmd;
    const uint8_t buffer_length;

    uint8_t *rx_buffer;
    uint8_t rx_length;

public:
    ModbusCommandSender(uint8_t *tx_buffer, uint8_t tx_length, uint8_t *rx_buffer, uint8_t rx_length)
        : port(NULL),
          delay_in_ms(100),
          controlPin(0),
          reader(NULL),
          max_attempts(3),
          buffer_cmd((const uint8_t *)tx_buffer),
          buffer_length((const uint8_t)tx_length),
          rx_buffer(rx_buffer),
          rx_length(rx_length)
    {
    }

    ~ModbusCommandSender()
    {
        delete reader;
    }
    
    ModbusCommandSender &setConfig(HardwareSerial *port, uint8_t controlPin);
    ModbusCommandSender &setAttempts(uint8_t max_attempts);

    template <class Treader>
    ModbusCommandSender &setReader()
    {
        this->reader = new Treader();
        return *this;
    }

    LinkedList<uint16_t> execute();
};

#endif  // SENSORS_MODBUS_COMMAND_SENDER_H
