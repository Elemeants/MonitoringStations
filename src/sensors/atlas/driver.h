#if !defined(SENSORS_ATLAS_DRIVER_H)
#define SENSORS_ATLAS_DRIVER_H

#include "i2c/import.h"

enum AtlasSensorType
{
    ATLAS_PH,
    ATLAS_EC
};

enum AtlasSensorStatus
{
    ATLAS_STATUS_SUCCESS,
    ATLAS_STATUS_FAIL,
    ATLAS_STATUS_PENDING,
    ATLAS_STATUS_NO_DATA
};

class AtlasI2CSensor : public I2CDevice
{
private:
    AtlasSensorType _type;
    AtlasSensorStatus _status;
    char internal_buffer[32];

    const __FlashStringHelper *sensor_typename()
    {
        switch (_type)
        {
        case ATLAS_PH:
            return F("pH");
        case ATLAS_EC:
            return F("EC");
        }
        return F("");
    }

protected:
    float last_value;

public:
    AtlasI2CSensor(uint8_t addr, AtlasSensorType type) : _type(type), _status(ATLAS_STATUS_NO_DATA)
    {
        setAddress(addr);
    }

    void setup();
    void update();
    void registerMeasure();
    AtlasSensorStatus status();
    float send_read();
};

#endif // SENSORS_ATLAS_DRIVER_H
