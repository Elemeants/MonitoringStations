#include "api.h"

#include <HardwareSerial.h>
#include <WString.h>

#include "driver/adafruit_gps_ultimate.h"
#include "common.h"

static HardwareSerial *gpsSerial = &Serial2;
static LocationData_t locationData;
static GPSStatus_e gpsStatus;
static Adafruit_GPS gps = Adafruit_GPS(gpsSerial);

static GPSStatus_e gps_update_task()
{
    uint32_t start_time = millis();
    while ((millis() - start_time) < GPS_UPDATE_TIMEOUT_MS)
    {
        (void)gps.read();
        if (gps.newNMEAreceived())
        {
            if (!gps.parse(gps.lastNMEA()))
                continue;
        }
        if ((millis() - start_time) > GPS_UPDATE_REQUEST_MS)
        {
            if (gps.fix)
            {
                locationData = {
                    gps.longitudeDegrees,
                    gps.latitudeDegrees,
                    gps.altitude};
                return GPS_OK;
            }
            else
            {
                return GPS_ERROR;
            }
        }
    }
    return GPS_TIMEOUT_ERROR;
}

static void core1_task_begin_gps(void *_)
{
    bool gpsBegined = false;
    while (!gpsBegined)
    {
        gps.begin(GPS_DEFAULT_BAUDRATE);
    }

    gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
    gps.sendCommand(PGCMD_ANTENNA);

    while (1)
    {
        gpsStatus = gps_update_task();
        switch (gpsStatus)
        {
        case GPS_OK:
            logger << LOG_INFO << F("Gps updated successfully [")
                   << locationData.latitude << ":" << locationData.longitude << "]"
                   << EndLine;
            break;
        case GPS_ERROR:
            logger << LOG_INFO << F("Error updating GPS location") << EndLine;
            break;
        case GPS_TIMEOUT_ERROR:
            logger << LOG_INFO << F("Timeout updating GPS location") << EndLine;
            break;
        }
    }
}

const __FlashStringHelper *GpsStatusToStr(GPSStatus_e st)
{
    switch (st)
    {
    case GPS_OK:
        return F("OK");
    case GPS_ERROR:
        return F("ERROR");
    case GPS_TIMEOUT_ERROR:
        return F("TIMEOUT");
    default:
        return F("");
    }
}

void DEVICES_GPS_Init()
{
}

GPSStatus_e DEVICES_GPS_NetStatus()
{
    return gpsStatus;
}

bool DEVICES_GPS_IsConnected()
{
    return gpsStatus == GPS_OK;
}

void DEVICES_GPS_UpdateAsync()
{
}
