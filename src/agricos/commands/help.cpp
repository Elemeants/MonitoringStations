#include "../globals.h"
#include "cmd.h"

static void AgricosCli_CMD_Help(cmd *_)
{
    logger.log(AgricosCli.toString(), LOG_MASTER);
}

void AgricosCli_Add_Help()
{
    Command cmd = AgricosCli.addCommand("help", AgricosCli_CMD_Help);
    cmd.setDescription(" . Shows help for CLI");
}