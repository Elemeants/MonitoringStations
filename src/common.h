#if !defined(COMMON_HEADER_H)
#define COMMON_HEADER_H

#include "i2c/import.h"
#include "logger/serial_logger.h"
#include "registers/import.h"
#include "types/isensor.h"
#include "types/itime_provider.h"
#include "types/kernel_task.h"
#include "types/register.h"
#include "types/rtc_mode.h"
#include "types/trigger_core_task.h"
#include "utils/array_utils.h"
#include "utils/datetime.h"
#include "utils/eeprom_utils.h"
#include "utils/error_codes.h"
#include "utils/free_memory.h"
#include "utils/linked_list.h"
#include "utils/linked_list_utils.h"

extern ITimeProvider *TimeProvider;
extern _MeasureRegister *MeasureRegister;
extern _SensorsRegister SensorsRegister;
extern _ITaskRegister SetupTasksRegister;

extern _ITaskRegister PostLoopTaskRegister;
extern _ITaskRegister PreLoopTaskRegister;

namespace Configuration
{
extern bool isModuleEnabled();
extern void readStationCode();
extern void readUrlServer();

extern eLogLevel_t readLogLevel();
extern uint8_t readRTCMode();
extern uint8_t isAdjustRTCEnabled();

extern Time_s readAdjustTime();
}  // namespace Configuration

#endif  // COMMON_HEADER_H
