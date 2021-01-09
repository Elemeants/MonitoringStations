#include "cmd.h"

#include "../globals.h"

static void AgricosCli_CMD_Status(cmd *_)
{
    logger  << LOG_MASTER 
            << LOGGER_TEXT_YELLOW 
            << F(" Show station status... in progress.") 
            << EndLine;
}

void AgricosCli_Add_Status()
{
    AgricosCli.addCommand("status", AgricosCli_CMD_Status);
}