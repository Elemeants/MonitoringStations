#if !defined(__AGRICOS_COMMANDS_TESTS_DEVICES_H)
#define __AGRICOS_COMMANDS_TESTS_DEVICES_H

#include "../../globals.h"
#include "../../devices.h"

struct CliTestId_t
{
    const char *id;
    void (*callback)();
};

extern void AgricosCli_CMD_Test_Led();
extern void AgricosCli_CMD_Test_MicroSD();

extern CliTestId_t CliTests[];

#endif  // __AGRICOS_COMMANDS_TESTS_DEVICES_H
