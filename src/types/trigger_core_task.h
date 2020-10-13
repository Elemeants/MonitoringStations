#ifndef TRIGGER_CORE_TASK
#define TRIGGER_CORE_TASK

#include "../utils/datetime.h"

typedef bool (*TriggerCoreTask)(Time_s time);

#endif // !TRIGGER_CORE_TASK