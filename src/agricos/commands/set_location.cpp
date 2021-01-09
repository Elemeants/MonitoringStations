#include "../globals.h"
#include "cmd.h"

static void AgricosCli_CMD_SetLocation(cmd *_)
{
    Command cmd(_);
    float lat = cmd.getArgument("lat").getValue().toFloat();
    float lng = cmd.getArgument("lng").getValue().toFloat();

    logger << LOG_MASTER
           << F(" . Set gps as lat: ")
           << LOGGER_TEXT_YELLOW << lat << LOGGER_TEXT_RESET
           << F(", lng: ")
           << LOGGER_TEXT_YELLOW << lng << LOGGER_TEXT_RESET
           << F("... ");

    Configuration::updadteGPSLat(lat);
    Configuration::updadteGPSLat(lng);

    logger << LOGGER_TEXT_GREEN << F(" # OK") << EndLine;
}

void AgricosCli_Add_SetLocation()
{
    Command cmd = AgricosCli.addCommand("gps", AgricosCli_CMD_SetLocation);
    cmd.addArgument("lat");
    cmd.addArgument("lng");
    cmd.setCaseSensetive(true);
    cmd.setDescription(" Sets gps device manually location");
}