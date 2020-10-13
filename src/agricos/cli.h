#if !defined(AGRICOS_CLI_H)
#define AGRICOS_CLI_H

#include <SimpleCLI.h>
#include <HardwareSerial.h>

extern HardwareSerial &CliSerialPort;
extern SimpleCLI AgricosCli;

extern void AgricosCli_CheckCommands(void);
extern void AgricosCli_Setup(void);

#endif // AGRICOS_CLI_H
