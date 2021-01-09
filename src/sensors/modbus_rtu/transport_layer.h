#if !defined(__SENSORS_MODBUS_RTU_TRANSPORT_LAYER_H)
#define __SENSORS_MODBUS_RTU_TRANSPORT_LAYER_H

#include "HardwareSerial.h"

#define MODBUS_RS485_BAUDRATE 9600

class ModbusRTULayer
{
    HardwareSerial &hwSerial;
    uint8_t ctrlPin;

    uint16_t delay_ms;
    uint8_t max_attempts;

public:
    ModbusRTULayer(HardwareSerial &port, uint8_t ctrlPin)
        : hwSerial(port),
          ctrlPin(ctrlPin),
          delay_ms(100U),
          max_attempts(3)
    {
    }

    void init();

    bool executeCommand(uint8_t *tx_buffer, uint8_t tx_len, uint8_t *rx_buffer, uint8_t rx_len);
};

#endif  // __SENSORS_MODBUS_RTU_TRANSPORT_LAYER_H
