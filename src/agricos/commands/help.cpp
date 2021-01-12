#include "../globals.h"
#include "cmd.h"

static void AgricosCli_CMD_Help(cmd *_)
{
    logger << LOG_MASTER << EndLine << AgricosCli.toString();
}

void AgricosCli_Add_Help()
{
    Command cmd = AgricosCli.addCommand("help", AgricosCli_CMD_Help);
    cmd.setDescription(" . Shows help for CLI");
}