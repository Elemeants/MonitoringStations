#if !defined(DEVICES_GPS_LOCATION_DATA_H)
#define DEVICES_GPS_LOCATION_DATA_H

#include "WString.h"

// Datatype for gps information.
struct LocationData_t
{
    // Longitude in degrees
    float longitude;
    // Latitude in degrees
    float latitude;
    // Altitude in degrees
    float altitude;

    // Default string transformation
    String toString()
    {
        String str = "Lon: ";
        str += String(this->longitude, 4);
        str += ", Lat: ";
        str += String(this->latitude, 4);
        str += ", Alt: ";
        str += String(this->altitude, 4);
        return str;
    }
};
typedef struct LocationData_t LocationData_t;

#endif  // DEVICES_GPS_LOCATION_DATA_H
