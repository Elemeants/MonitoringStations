#if !defined(AGRICOS_SENSOR_ISENSOR_H)
#define AGRICOS_SENSOR_ISENSOR_H

#include <stddef.h>
#include <stdint.h>

#include "../logger/ikernel_logger.h"
#include "../utils/sensor_protocol_str.h"
#include "registers/measure_register.h"
#include "registers/variable_register.h"
#include "sensor_protocols.h"
#include "variable_types.h"

extern _MeasureRegister* MeasureRegister;
extern _VariableRegister* VariableRegister;

struct SensorInfo_t
{
    const char* id;
    SensorProtocols_e protocol;

    LinkedList<Variable_t> variables;
};

class ISensor
{
protected:
    SensorInfo_t info;

    template <VariableType_e Vtype>
    void setMeasureValue(float value)
    {
        for_in_range(uint8_t, i, 0, info.variables.size())
        {
            Variable_t var = info.variables[i];
            if (var.type == Vtype)
            {
                var.measure = value;
            }
        }
    }

public:
    ISensor(const char* id, SensorProtocols_e protocol, const VariableType_e vars[], uint8_t length)
    {
        info.id = id;
        info.protocol = protocol;
        for_in_range(uint8_t, i, 0, length)
        {
            Variable_t var = VariableRegister->registerVariable(vars[i]);
            info.variables.add(var);
        }
    }

    virtual void setup() = 0;
    virtual void update() = 0;

    const char* getId() { return this->info.id; }

    virtual void registerMeasure()
    {
        for_in_range(uint8_t, i, 0, info.variables.size())
        {
            MeasureRegister->addMeasure(info.variables[i]);
        }
    }

    virtual void logSensorData()
    {
        logger << LOG_INFO << F(" Sensor ") << info.id << F(" -> Protocol: ") << SensorProtocolToStr(info.protocol) << EndLine;
        logger << LOG_INFO << F("               Variables: ");
        for_in_range(uint8_t, i, 0, info.variables.size())
        {
            Variable_t var = info.variables[i];
            logger << VariableTypeToStr(var.type);
            if (i < info.variables.size() - 1)
            {
                logger << F(", ");
            }
        }
    }

    virtual void logAsTable(Print& cout)
    {
    }

    SensorInfo_t *getInfo() { return &info; }
};

#endif  // AGRICOS_SENSOR_ISENSOR_H
