#include "cli.h"

#include <Arduino.h>

#include "config_provider.h"
#include "devices/include.h"
#include "globals.h"

HardwareSerial &CliSerialPort = Serial;
SimpleCLI AgricosCli;

void AgricosCli_CheckCommands(void)
{
    static char input[50];
    static bool command_detected = false;
    static bool cmd_overflow = false;
    static uint8_t in_index = 0;

    while (CliSerialPort.available())
    {
        char c = CliSerialPort.read();

        if (c == '\n')
        {
            command_detected = true;
            in_index = 0;
            break;
        }

        input[in_index] = c;
        in_index++;

        if (in_index >= array_size(input))
        {
            cmd_overflow = true;
            in_index = 0;
            break;
        }
    }
    if (cmd_overflow)
    {
        logger << LOG_ERROR << F(" # Agricos@Cli > ") << input << EndLine;
        cmd_overflow = false;
        for_in_range(uint8_t, i, 0, sizeof(input)) { input[i] = 0x00; }
    }

    if (command_detected)
    {
        logger << LOG_MASTER << F(" # Agricos@Cli > ") << input << EndLine;
        AgricosCli.parse(input);
        command_detected = false;
        for_in_range(uint8_t, i, 0, sizeof(input)) { input[i] = 0x00; }
    }
}

Command AddCommandToAgricosCli(const char *cmd_name, const char *argv, const char *description, void (*callback)(cmd *_cmd))
{
    Command cmd = AgricosCli.addCommand(cmd_name, callback);
    cmd.addArgument(argv);
    cmd.setCaseSensetive(true);
    cmd.setDescription(description);
    return cmd;
}

// Callback in case of an error
void errorCallback(cmd_error *e)
{
    CommandError cmdError(e);  // Create wrapper object

    Serial.print("ERROR: ");
    Serial.println(cmdError.toString());

    if (cmdError.hasCommand())
    {
        Serial.print("Did you mean \"");
        Serial.print(cmdError.getCommand().toString());
        Serial.println("\"?");
    }
}

void AgricosCli_Setup(void)
{
    AgricosCli.setOnError(errorCallback);  // Set error Callback

    AgricosCli.addCommand("help", [](cmd *cmd) -> void {
        logger.log(AgricosCli.toString(), LOG_MASTER);
    });

    AgricosCli.addCommand("status", [](cmd *cmd) -> void {

    });

    AgricosCli.addCommand("conf", [](cmd *cmd) -> void {
        Configuration::printConfiguration();
    });

    AddCommandToAgricosCli("code", "v", " Sets the device code", [](cmd *_cmd) -> void {
        Command cmd(_cmd);
        String deviceCode = cmd.getArgument("v").getValue();
        logger << LOG_MASTER << F(" . Set device code as: ") << deviceCode << EndLine;
        deviceCode.toCharArray(Configuration::DeviceCode, DEVICE_CODE_LENGHT);
        Configuration::updateStationCode();
    });

    AddCommandToAgricosCli("host", "v", " Sets the host url", [](cmd *_cmd) -> void {
        Command cmd(_cmd);
        String hostUrl = cmd.getArgument("v").getValue();
        logger << LOG_MASTER << F(" Set host url as: ") << hostUrl << EndLine;
        hostUrl.toCharArray(Configuration::ServerUrl, SERVER_URL_LENGHT);
        Configuration::updateUrlServer();
    });

    AddCommandToAgricosCli("log", "v", " Sets the log level", [](cmd *_cmd) -> void {
        Command cmd(_cmd);
        int logLv = cmd.getArgument("v").getValue().toInt();
        logger << LOG_MASTER << F(" Set log level as: ") << logLv << EndLine;
    });

    AddCommandToAgricosCli("rtc", "v", " Sets the rtc mode", [](cmd *_cmd) -> void {
        Command cmd(_cmd);
        int logLv = cmd.getArgument("v").getValue().toInt();
        logger << LOG_MASTER << F(" Set log level as: ") << logLv << EndLine;
    });

    AddCommandToAgricosCli("time", "v", " Sets the time of the RTC", [](cmd *_cmd) -> void {
        Command cmd(_cmd);
        String logLv = cmd.getArgument("v").getValue();
        logger << LOG_MASTER << F(" Set UTC time as: ") << logLv << EndLine;
    });

    AddCommandToAgricosCli("test", "v", " tests some device", [](cmd *_cmd) -> void {
        Command cmd(_cmd);
        String testCode = cmd.getArgument("v").getValue();

        if (testCode == "led")
        {
            logger << LOG_MASTER << LOGGER_TEXT_GREEN << F(" Blinking status led every 100ms while 1s ") << EndLine;
            for_in_range(uint8_t, i, 0, 10)
            {
                StatusLed::blink();
                delay(100);
            }
            logger << LOG_MASTER << LOGGER_TEXT_GREEN << F(" END TEST") << EndLine;
        }
    });
}
