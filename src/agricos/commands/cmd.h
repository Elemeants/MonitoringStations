#if !defined(__AGRICOS_CLI_COMMANDS_H)
#define __AGRICOS_CLI_COMMANDS_H

#include "base.h"

extern void AgricosCli_Add_ShowConfiguration();
extern void AgricosCli_Add_ShowSensors();
extern void AgricosCli_Add_Help();
extern void AgricosCli_Add_Status();

extern void AgricosCli_Add_SetLocation();
extern void AgricosCli_Add_SetDeviceCode();
extern void AgricosCli_Add_SetDeviceHost();
extern void AgricosCli_Add_SetLogLevel();
extern void AgricosCli_Add_SetRtcMode();
extern void AgricosCli_Add_SetDateTime();

extern void AgricosCli_Add_Test();
extern void AgricosCli_Add_Reset();

#endif  // __AGRICOS_CLI_COMMANDS_H
