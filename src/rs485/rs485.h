#if !defined(DRIVER_RS485_H)
#define DRIVER_RS485_H

#include <HardwareSerial.h>
#include <Stream.h>

class RS485 : public Stream
{
    HardwareSerial &port;
    uint8_t RWControl;
public:
    RS485(HardwareSerial &port, uint8_t RWControl)
        : port(port), RWControl(RWControl) { }

    void begin(uint32_t baudrate);
    void end();

    void startTransmission();
    void startReception();

    int available();
    int read();
    int peek();
    size_t write(uint8_t);
};

#endif // DRIVER_RS485_H
