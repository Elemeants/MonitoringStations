#include "serial_logger.h"

eLogLevel_t SerialLogger::log_lvl = LOGGER_LOG_LEVEL;

void SerialLogger::begin(uint32_t baudrate)
{
  port->begin(baudrate);
}

void SerialLogger::end()
{
  port->end();
}

void SerialLogger::flush()
{
  port->flush();
}

static SerialLogger serialLogger;
IKernelLogger &logger = serialLogger;