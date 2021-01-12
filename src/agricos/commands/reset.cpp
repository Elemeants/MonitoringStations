#include "../core.h"
#include "../globals.h"
#include "cmd.h"

static void AgricosCli_CMD_Reset(cmd *_)
{
    OS_reset();
}

void AgricosCli_Add_Reset()
{
    Command cmd = AgricosCli.addCommand("reset", AgricosCli_CMD_Reset);
    cmd.setDescription(" Resets the stations");
}