#if !defined(REGISTERS_SENSORS_REGISTER_H)
#define REGISTERS_SENSORS_REGISTER_H

#include "types/isensor.h"
#include "types/register.h"
#include "utils/linked_list_utils.h"

class _SensorsRegister : public IRegister<ISensor*>
{
private:
    bool _isReading = false;

public:
    void setup()
    {
        _for_each(bus, task, ISensor*)
            task->setup();
    }

    void run()
    {
        _isReading = true;
        _for_each(bus, task, ISensor*)
        {
            task->update();
            task->registerMeasure(0);
        }
        _isReading = false;
    }

    void registerMeasures()
    {
        _for_each(bus, task, ISensor*)
            task->registerMeasure(0);
    }

    bool isReading() { return _isReading; }
};

#endif  // REGISTERS_SENSORS_REGISTER_H
