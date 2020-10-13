#if !defined(AGRICOS_GLOBAL_INSTANCES_H)
#define AGRICOS_GLOBAL_INSTANCES_H

#include "common.h"
#include "config_provider.h"

extern ITimeProvider *TimeProvider;
extern _MeasureRegister *MeasureRegister;
extern _SensorsRegister SensorsRegister;
extern _ITaskRegister SetupTasksRegister;

extern _ITaskRegister PostLoopTaskRegister;
extern _ITaskRegister PreLoopTaskRegister;

extern void (*AgricosCore_onFail)(void);
extern void (*AgricosCore_onSuccess)(void);
extern bool (*AgricosCore_OutputTask)(void);

#endif  // AGRICOS_GLOBAL_INSTANCES_H
