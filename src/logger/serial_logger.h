#ifndef KERNEL_LOGGER_H
#define KERNEL_LOGGER_H

#include "config.h"
#include "ikernel_logger.h"

class SerialLogger : public IKernelLogger
{
protected:
  // [Reference] Port where is logging
  HardwareSerial *port;
  // [Static Attribute] Global log level
  static eLogLevel_t log_lvl;

public:
  SerialLogger()
      : IKernelLogger(LOGGER_SERIAL_PORT), port(&LOGGER_SERIAL_PORT)
  {
    setLogLevel(SerialLogger::log_lvl);
  }

  // [Public Method] Begins serial communication
  void begin() override
  {
    begin(LOGGER_BAUDRATE);
  }
  // [Public Method] Begins serial communication
  void begin(uint32_t) override;
  // [Public Method] Ends serial communication
  void end() override;
  // [Public Method] Flush implementation
  void flush();
};

#endif // !KERNEL_LOGGER_H