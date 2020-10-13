#if !defined(AGRICOS_SENSOR_ISENSOR_H)
#define AGRICOS_SENSOR_ISENSOR_H

class ISensor
{
public:
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void registerMeasure(uint8_t ) = 0;
};

#endif // AGRICOS_SENSOR_ISENSOR_H
