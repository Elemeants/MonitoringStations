#include "cmd.h"

#include "../globals.h"

static void AgricosCli_CMD_ShowConfiguration(cmd *_)
{
    Configuration::printConfiguration();
}

void AgricosCli_Add_ShowConfiguration()
{
    Command cmd = AgricosCli.addCommand("config", AgricosCli_CMD_ShowConfiguration);
    cmd.setDescription(" Shows the actual configuration");
}