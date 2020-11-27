#include "cmd_sender.h"

ModbusCommandSender &ModbusCommandSender::setConfig(HardwareSerial *port, uint8_t controlPin)
{
    this->port = port;
    this->port->setTimeout(500U);
    this->controlPin = controlPin;
    return *this;
}

ModbusCommandSender &ModbusCommandSender::setAttempts(uint8_t max_attempts)
{
    this->max_attempts = max_attempts;
    return *this;
}

LinkedList<uint16_t> ModbusCommandSender::execute()
{
    uint8_t attempts = 0;

    if (!this->port || !this->buffer_cmd || this->controlPin == 0)
    {
        goto error;
    }

    do
    {
        clear_array(this->rx_buffer, this->rx_length);

        digitalWrite(this->controlPin, HIGH);
        port->write(this->buffer_cmd, this->buffer_length);
        digitalWrite(this->controlPin, LOW);

        delay(this->delay_in_ms);

        port->readBytes(this->rx_buffer, this->rx_length);

        uint16_t crc = calculate_crc16(this->rx_buffer, this->rx_length - sizeof(uint16_t));
        uint16_t exp_crc = rx_buffer[rx_length - 1] | rx_buffer[rx_length - 2] << 8;

        if (crc == exp_crc)
        {
            if (reader)
            {
                return reader->parse(this->rx_buffer, this->rx_length);
            }
            goto error;
        }
    } while (attempts < this->max_attempts);

error:
    return LinkedList<uint16_t>();
}
