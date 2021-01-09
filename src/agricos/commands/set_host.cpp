#include "../globals.h"
#include "cmd.h"

static void AgricosCli_CMD_SetDeviceHost(cmd *_)
{
    Command cmd(_);
    String hostUrl = cmd.getArgument("v").getValue();
    hostUrl.toCharArray(Configuration::ServerUrl, SERVER_URL_LENGHT);

    logger << LOG_MASTER
           << F(" . Set host url as: ")
           << LOGGER_TEXT_YELLOW << Configuration::ServerUrl << LOGGER_TEXT_RESET;

    Configuration::updateUrlServer();

    logger << LOGGER_TEXT_GREEN << F(" # OK") << EndLine;
}

void AgricosCli_Add_SetDeviceHost()
{
    Command cmd = AgricosCli.addCommand("host", AgricosCli_CMD_SetDeviceHost);
    cmd.addArgument("v");
    cmd.setCaseSensetive(true);
    cmd.setDescription(" Sets device host");
}