#include "transport_layer.h"

#include "common.h"

void ModbusRTULayer::init()
{
    pinMode(ctrlPin, OUTPUT);
    hwSerial.begin(MODBUS_RS485_BAUDRATE);
    hwSerial.setTimeout(500U);  // 500ms
}

bool ModbusRTULayer::executeCommand(uint8_t *tx_buffer, uint8_t tx_len, uint8_t *rx_buffer, uint8_t rx_len)
{
    uint8_t attempts = 0;
    if (!tx_buffer || !rx_buffer || tx_len == 0 || rx_len == 0)
    {
        return false;
    }

    do
    {
        memset(rx_buffer, 0x00, rx_len);
        digitalWrite(ctrlPin, HIGH);
        hwSerial.write(tx_buffer, tx_len);
        digitalWrite(ctrlPin, LOW);
        delay(delay_ms);

        hwSerial.readBytes(rx_buffer, rx_len);

        uint16_t crc = calculate_crc16(rx_buffer, rx_len - sizeof(uint16_t));
        uint16_t expected_crc = rx_buffer[rx_len - 1] | rx_buffer[rx_len - 2] << 8;

        if (crc == expected_crc)
        {
            return true;
        }

        attempts++;
    } while (attempts < max_attempts);
    return false;
}