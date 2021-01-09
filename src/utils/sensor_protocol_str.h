#if !defined(__UTILS_SENSOR_PROTOCOL_TO_STR_H)
#define __UTILS_SENSOR_PROTOCOL_TO_STR_H

#include <Arduino.h>

#include "../types/sensor_protocols.h"

const __FlashStringHelper *SensorProtocolToStr(SensorProtocols_e protocol);

#endif  // __UTILS_SENSOR_PROTOCOL_TO_STR_H
