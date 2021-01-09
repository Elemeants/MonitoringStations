#include "include.h"

void AgricosCli_CMD_Test_MicroSD()
{
    logger << LOG_MASTER
           << LOGGER_TEXT_GREEN
           << F(" Trying to begin micro sd card")
           << EndLine;
    MicroSD_Init(SD_CS_PIN);
    logger << LOG_MASTER << LOGGER_TEXT_YELLOW << F(" END TEST") << EndLine;
}