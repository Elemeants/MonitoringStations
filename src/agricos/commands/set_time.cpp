#include "../globals.h"
#include "cmd.h"

static void AgricosCli_CMD_SetDateTime(cmd *_)
{
    Command cmd(_);
    String time = cmd.getArgument("v").getValue();

    // TODO: Parse string time into Time_s -> adjust rtc, set system clock.
    logger << LOG_MASTER
           << F(" . Set UTC time as: ")
           << LOGGER_TEXT_YELLOW << time << LOGGER_TEXT_RESET
           << F(" # Still in progress")
           << EndLine;
}

void AgricosCli_Add_SetDateTime()
{
    Command cmd = AgricosCli.addCommand("time", AgricosCli_CMD_SetDateTime);
    cmd.addArgument("v");
    cmd.setCaseSensetive(true);
    cmd.setDescription(" Sets the UTC time of the RTC");
}