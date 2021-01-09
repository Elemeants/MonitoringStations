#include "../core.h"
#include "../globals.h"
#include "cmd.h"

static void AgricosCli_CMD_SetRtcMode(cmd *_)
{
    Command cmd(_);
    RTCMode_e rtcMode = (RTCMode_e)cmd.getArgument("v").getValue().toInt();

    logger << LOG_MASTER
           << F(" . Set rtc mode as: ")
           << LOGGER_TEXT_YELLOW << GetStringRtcMode(rtcMode) << LOGGER_TEXT_RESET;

    Configuration::storeRTCMode(rtcMode);
    AgricosSysStatus.sysRtcMode = rtcMode;

    logger << LOGGER_TEXT_GREEN << F(" # OK") << EndLine;
}

void AgricosCli_Add_SetRtcMode()
{
    Command cmd = AgricosCli.addCommand("rtc", AgricosCli_CMD_SetRtcMode);
    cmd.addArgument("v");
    cmd.setCaseSensetive(true);
    cmd.setDescription(" Sets device rtc post mode");
}