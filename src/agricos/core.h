#if !defined(AGRICOS_CORE_H)
#define AGRICOS_CORE_H

#include "common.h"
#include "config.h"
#include "config_provider.h"
#include "devices/include.h"
#include "globals.h"
#include "sensors/include.h"
#include "sys_status.h"

extern void AgricosCore_Init(void);
extern void AgricosCore_Task(void);
extern void AgricosCore_InitRegisters(void);

extern void throw_error(uint8_t errorCode);

extern AgricosCore_Status_t AgricosSysStatus;

extern inline void OS_init(void);

extern inline void OS_reset(void);

#endif  // AGRICOS_CORE_H
