#if !defined(__AGRICOS_CLI_COMMANDS_BASE_H)
#define __AGRICOS_CLI_COMMANDS_BASE_H

#include <SimpleCLI.h>
#include <HardwareSerial.h>
#include "../board.h"

#define CLI_BUFFER_LENGTH 64

extern HardwareSerial &CliSerialPort;

extern SimpleCLI AgricosCli;

extern void AgricosCLI_CheckIfExistCommand();

extern void AgricosCLI_OnError(cmd_error *e);

#endif  // __AGRICOS_CLI_COMMANDS_BASE_H
