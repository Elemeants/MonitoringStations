#include "../globals.h"
#include "cmd.h"

static void AgricosCli_CMD_SetLogLevel(cmd *_)
{
    Command cmd(_);
    eLogLevel_t logLv = (eLogLevel_t)cmd.getArgument("v").getValue().toInt();

    logger << LOG_MASTER
           << F(" . Set log level as: ")
           << LOGGER_TEXT_YELLOW << GetStringLogLevel(logLv) << LOGGER_TEXT_RESET;

    Configuration::storeLogLevel(logLv);
    logger.setLogLevel(logLv);

    logger << LOGGER_TEXT_GREEN << F(" # OK") << EndLine;
}

void AgricosCli_Add_SetLogLevel()
{
    Command cmd = AgricosCli.addCommand("loglv", AgricosCli_CMD_SetLogLevel);
    cmd.addArgument("v");
    cmd.setCaseSensetive(true);
    cmd.setDescription(" Sets device log level");
}