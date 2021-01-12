#include "cli.h"

#include "commands/base.h"
#include "commands/cmd.h"

void AgricosCli_Setup(void)
{
    AgricosCli.setOnError(AgricosCLI_OnError);

    AgricosCli_Add_ShowConfiguration();
    AgricosCli_Add_ShowSensors();
    AgricosCli_Add_Help();
    AgricosCli_Add_Status();
    
    AgricosCli_Add_SetLocation();
    AgricosCli_Add_SetDeviceCode();
    AgricosCli_Add_SetDeviceHost();
    AgricosCli_Add_SetLogLevel();
    AgricosCli_Add_SetRtcMode();
    AgricosCli_Add_SetDateTime();

    AgricosCli_Add_Test();
    AgricosCli_Add_Reset();
}
