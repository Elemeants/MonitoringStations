#if !defined(AGRICOS_SENSORS_BUS_H)
#define AGRICOS_SENSORS_BUS_H

typedef enum {
    AGRICOS_SENSOR_APOGEE_SP,
    AGRICOS_SENSOR_APOGEE_SQ,
    AGRICOS_SENSOR_APOGEE_SV,
    AGRICOS_SENSOR_DAVIS_SENSOR,
    AGRICOS_SENSOR_,
    AGRICOS_SENSOR_,
} AgricosSensorType_e;

struct AgricosSensor
{
    const char *name;
    AgricosSensorType_e type;
    
    
};

#endif  // AGRICOS_SENSORS_BUS_H
