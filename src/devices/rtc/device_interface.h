#if !defined(DEVICEs_RTC_DEVICE_INTERFACE_H)
#define DEVICEs_RTC_DEVICE_INTERFACE_H

#include "types/itime_provider.h"
#include "i2c/i2c_device.h"

class IRTCI2c : public I2CDevice, public ITimeProvider
{
public:

    virtual bool begin(uint8_t addr);

    virtual void adjustRtc(const char *date, const char *time) = 0;
    virtual void adjustRtc(uint16_t year, uint8_t month, uint8_t day, uint8_t week,
                           uint8_t hour, uint8_t minute, uint8_t second) = 0;
    void adjustRtc(DateTime dateTime)
    {
        adjustRtc(Time_s(dateTime));
    }
    void adjustRtc(Time_s time)
    {
        adjustRtc(time.year, time.month, time.day, 0, time.hour, time.minute, time.second);
    }

    virtual DateTime toDateTime() = 0;
    DateTime toUtcDateTime() { return toUtcTime_s().toDateTime(); }

    Time_s toTime_s() { return Time_s(toDateTime()); }
    Time_s toUtcTime_s() { return toTime_s().toUtcTime(); }

    Time_s getTime() {
        return toTime_s();
    }

    virtual void update();
};

#endif // DEVICEs_RTC_DEVICE_INTERFACE_H
