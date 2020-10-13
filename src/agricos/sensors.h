#if !defined(AGRICOS_SENSORS_H)
#define AGRICOS_SENSORS_H

#include "common.h"
#include "sensors/include.h"

#define CODE_PH "pH"
#define CODE_EC "eC"
#define CODE_CO2 "co2"
#define CODE_PAR "sp"
#define CODE_IRR "sq"
#define CODE_TEMPERATURE "st"
#define CODE_HUMIDITY "rv"

#define IRR_ANALOG_CHANNEL A14
#define PAR_ANALOG_CHANNEL A15

void AgricosSensors_Init();

#endif  // AGRICOS_SENSORS_H
