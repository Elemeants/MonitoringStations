#include "../globals.h"
#include "cmd.h"

static void AgricosCli_CMD_SetDeviceCode(cmd *_)
{
    Command cmd(_);
    String deviceCode = cmd.getArgument("v").getValue();
    deviceCode.toCharArray(Configuration::DeviceCode, DEVICE_CODE_LENGHT);

    logger << LOG_MASTER
           << F(" . Set device code as: ")
           << LOGGER_TEXT_YELLOW << Configuration::DeviceCode << LOGGER_TEXT_RESET;

    Configuration::updateStationCode();

    logger << LOGGER_TEXT_GREEN << F(" # OK") << EndLine;
}

void AgricosCli_Add_SetDeviceCode()
{
    Command cmd = AgricosCli.addCommand("code", AgricosCli_CMD_SetDeviceCode);
    cmd.addArgument("v");
    cmd.setCaseSensetive(true);
    cmd.setDescription(" Sets device code");
}