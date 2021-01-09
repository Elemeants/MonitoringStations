#include "base.h"

#include "../config.h"
#include "../globals.h"

HardwareSerial &CliSerialPort = CLI_INTERFACE_SERIAL;
SimpleCLI AgricosCli;

enum CMDParseStatus_e
{
    CMD_DETECTED,
    CMD_OVERFLOW,
    CMD_PARSING
};

void AgricosCLI_CheckIfExistCommand(void)
{
    static char input[CLI_BUFFER_LENGTH];
    static CMDParseStatus_e status = CMD_PARSING;
    static uint8_t in_index = 0;

    status = CMD_PARSING;

    while (CliSerialPort.available())
    {
        char c = CliSerialPort.read();

        if (c == '\n')
        {
            status = CMD_DETECTED;
            in_index = 0;
            break;
        }

        input[in_index] = c;
        in_index++;

        if (in_index >= array_size(input))
        {
            status = CMD_OVERFLOW;
            in_index = 0;
            break;
        }
    }

    switch (status)
    {
    case CMD_DETECTED:
        logger << LOG_MASTER << F(" # Agricos@Cli > ") << input << EndLine;
        AgricosCli.parse(input);
        break;
    case CMD_OVERFLOW:
        logger << LOG_ERROR << F(" # Agricos@Cli > ") << input << EndLine;
        break;
    // In case of some undefined behavior on status flag, or still parsing, this function ends here.
    default:
    case CMD_PARSING:
        return;
    }

    // If detected or overflow clean command buffer
    memset(&input, 0x00, CLI_BUFFER_LENGTH);
}

// Callback in case of an error on parsing
void AgricosCLI_OnError(cmd_error *e)
{
    CommandError cmdError(e);  // Create wrapper object

    logger << LOG_ERROR << cmdError.toString() << EndLine;

    if (cmdError.hasCommand())
    {
        logger  << LOG_ERROR 
                << F("Did you mean \"") 
                << cmdError.getCommand().toString() 
                << F("\"?") 
                << EndLine;
    }
}