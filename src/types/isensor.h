#if !defined(AGRICOS_SENSOR_ISENSOR_H)
#define AGRICOS_SENSOR_ISENSOR_H

#include <stddef.h>
#include <stdint.h>

#include "registers/measure_register.h"
#include "variable_types.h"

extern _MeasureRegister* MeasureRegister;

template <size_t Nvars>
class ISensor
{
protected:
    const char* sensor_name;
    const uint8_t NUM_VARS = Nvars;
    Variable_t variables[Nvars];

    template <VariableType_e Vtype>
    void setMeasureValue(float value)
    {
        for_in_range(uint8_t, i, 0, (uint8_t)Nvars)
        {
            Variable_t var = variables[i];
            if (var.type == Vtype)
            {
                var.measure = value;
            }
        }
    }

public:
    ISensor(const char* sensor_name, const VariableType_e types[Nvars])
        : sensor_name(sensor_name)
    {
        for_in_range(auto, i, 0, (uint8_t)Nvars)
        {
            variables[i] = {types[i], 0.0F};
        }
    }

    const char* getSensorName() { return this->sensor_name; }

    virtual void setup() = 0;
    virtual void update() = 0;

    virtual void registerMeasure()
    {
        for_in_range(uint8_t, i, 0, (uint8_t)Nvars)
        {
            Variable_t var = variables[i];
            MeasureRegister->addMeasure(var.measure, var.type);
        }
    }

    virtual void printSensorData(Print& cout)
    {
        cout.println(getSensorName());
    }
};

#endif  // AGRICOS_SENSOR_ISENSOR_H
