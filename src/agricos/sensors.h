#if !defined(__AGRICOS_SENSORS_H)
#define __AGRICOS_SENSORS_H

#include "board.h"
#include "common.h"
#include "sensors/include.h"

extern LinkedList<SensorInfo_t *> StationSensors;

void AgricosSensors_Init();
void AgricosSensors_Update();

#endif  // __AGRICOS_SENSORS_H
