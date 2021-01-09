#if !defined(MEASURE_TYPES_H)
#define MEASURE_TYPES_H

#include "utils/datetime.h"

typedef enum
{
    // Station variable measurement
    VARIABLE_TYPE_BATTERY,

    // Meteorology varaible measurement
    VARIABLE_TYPE_TEMPERATURE,
    VARIABLE_TYPE_HUMIDITY,
    VARIABLE_TYPE_RAIN,
    VARIABLE_TYPE_WIND_SPEED,
    VARIABLE_TYPE_WIND_DIRECTION,
    VARIABLE_TYPE_PREASSURE,
    VARIABLE_TYPE_VAPOR_PRESURE,

    // Radiation varaible
    VARIABLE_TYPE_PAR_RADIATION,
    VARIABLE_TYPE_UV_RADIATION,
    VARIABLE_TYPE_IRR_RADIATION,

    // Soil properties measurement
    VARIABLE_TYPE_PH,
    VARIABLE_TYPE_EC,
    VARIABLE_TYPE_SOIL_TEMPERATURE,
    VARIABLE_TYPE_SOIL_HUMIDITY,
    VARIABLE_TYPE_WATER_POTENTIAL,
    VARIABLE_TYPE_SOIL_SALINITY,

    // Crop variable measurement
    VARIABLE_TYPE_LEAF_HUMIDITY,
    VARIABLE_TYPE_LEAF_TEMPERATURE,
} VariableType_e;

typedef struct
{
    String id;
    VariableType_e type;
    float measure;
} Variable_t;

#endif  // MEASURE_TYPES_H
