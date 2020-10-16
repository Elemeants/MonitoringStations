#if !defined(AGRICOS_SENSOR_ISENSOR_H)
#define AGRICOS_SENSOR_ISENSOR_H

#include <stdint.h>

#include "variable_types.h"

class ISensor
{
public:
    virtual void setup() = 0;
    virtual void update() = 0;

    virtual void registerMeasure() = 0;
};

#endif  // AGRICOS_SENSOR_ISENSOR_H
