#if !defined(DEVICES_ADAFRUIT_GPS_API_H)
#define DEVICES_ADAFRUIT_GPS_API_H

#include "location_data.h"

class __FlashStringHelper;

// Timelimit for request update the gps
#define GPS_UPDATE_TIMEOUT_MS 1500
// Expected time in request gps location
#define GPS_UPDATE_REQUEST_MS 1000
// Default baudrate of serial comunitation
#define GPS_DEFAULT_BAUDRATE 9800

enum GPSStatus_e
{
    GPS_OK,
    GPS_ERROR,
    GPS_TIMEOUT_ERROR,
    GPS_END
};

const __FlashStringHelper *GpsStatusToStr(GPSStatus_e st);

namespace GPS
{
void init();
bool isConnected();
GPSStatus_e net_status();
void update();
};  // namespace GPS

#endif  // DEVICES_ADAFRUIT_GPS_API_H
