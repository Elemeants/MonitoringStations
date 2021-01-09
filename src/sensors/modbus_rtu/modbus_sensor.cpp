#include "modbus_sensor.h"

uint16_t ModbusSensor::readRegister(uint16_t reg)
{
    ModbusCmdBuilderOps_t cmd = ModbusCmdFactory::CreateReadCommand(deviceId, 1, reg);

    ModbusBuildCommand(cmd, tx_buffer, &tx_length, &rx_length);

    bool success = layer.executeCommand(tx_buffer, tx_length, rx_buffer, rx_length);
    if (!success)
    {
        return 0;
    }

    uint16_t response = ParseSingleRegisterCommand(rx_buffer, rx_length);
    return response;
}

void ModbusSensor::writeRegister(uint16_t reg, uint16_t value)
{
    LinkedList<uint16_t> data(1U, value);
    ModbusCmdBuilderOps_t cmd = ModbusCmdFactory::CreateWriteCommand(deviceId, data, 1U, reg);

    ModbusBuildCommand(cmd, tx_buffer, &tx_length, &rx_length);

    layer.executeCommand(tx_buffer, tx_length, rx_buffer, rx_length);
}

LinkedList<uint16_t> ModbusSensor::readMultiRegister(uint16_t reg, uint16_t no_regs)
{
    logger << LOG_DEBUG << F("                  ├-- Creating command...");
    ModbusCmdBuilderOps_t cmd = ModbusCmdFactory::CreateReadCommand(deviceId, no_regs, reg);

    ModbusBuildCommand(cmd, tx_buffer, &tx_length, &rx_length);
    logger << LOGGER_TEXT_GREEN << F(" # Ok") << EndLine;

    logger << LOG_DEBUG << F("                  ├-- Sending...");
    bool success = layer.executeCommand(tx_buffer, tx_length, rx_buffer, rx_length);
    if (!success)
    {
        logger << LOGGER_TEXT_RED << F(" # Error") << EndLine;
        return LinkedList<uint16_t>();
    }
    logger << LOGGER_TEXT_GREEN << F(" # Ok") << EndLine;

    logger << LOG_DEBUG << F("                  ├-- Parsing response...");
    LinkedList<uint16_t> response = ParseMultiRegisterCommand(rx_buffer, rx_length);
    logger << LOGGER_TEXT_GREEN << F(" # Ok") << EndLine;
    return response;
}