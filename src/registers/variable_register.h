#if !defined(__REGISTERS_VARIABLE_REGISTER_H)
#define __REGISTERS_VARIABLE_REGISTER_H

#include <stdint.h>

#include "../types/variable_types.h"
#include "../utils/vartype_str.h"

class _VariableRegister
{
    uint8_t cBATTERY;

    // Meteorology varaible measurement
    uint8_t cTEMPERATURE;
    uint8_t cHUMIDITY;
    uint8_t cRAIN;
    uint8_t cWIND_SPEED;
    uint8_t cWIND_DIRECTION;
    uint8_t cPREASSURE;
    uint8_t cVAPOR_PRESURE;

    // Radiation varaible
    uint8_t cPAR_RADIATION;
    uint8_t cUV_RADIATION;
    uint8_t cIRR_RADIATION;

    // Soil properties measurement
    uint8_t cPH;
    uint8_t cEC;
    uint8_t cSOIL_TEMPERATURE;
    uint8_t cSOIL_HUMIDITY;
    uint8_t cWATER_POTENTIAL;
    uint8_t cSOIL_SALINITY;

    // Crop variable measurement
    uint8_t cLEAF_HUMIDITY;
    uint8_t cLEAF_TEMPERATURE;

public:
    _VariableRegister()
        : cBATTERY(0),
          cTEMPERATURE(0),
          cHUMIDITY(0),
          cRAIN(0),
          cWIND_SPEED(0),
          cWIND_DIRECTION(0),
          cPREASSURE(0),
          cVAPOR_PRESURE(0),
          cPAR_RADIATION(0),
          cUV_RADIATION(0),
          cIRR_RADIATION(0),
          cPH(0),
          cEC(0),
          cSOIL_TEMPERATURE(0),
          cSOIL_HUMIDITY(0),
          cWATER_POTENTIAL(0),
          cSOIL_SALINITY(0),
          cLEAF_HUMIDITY(0),
          cLEAF_TEMPERATURE(0)
    {
    }

    Variable_t registerVariable(VariableType_e type)
    {
        String id = VariableTypeToCode(type);

        switch (type)
        {
        case VARIABLE_TYPE_BATTERY:
            cBATTERY++;
            id += cBATTERY;
            break;
        case VARIABLE_TYPE_TEMPERATURE:
            cTEMPERATURE++;
            id += cTEMPERATURE;
            break;
        case VARIABLE_TYPE_HUMIDITY:
            cHUMIDITY++;
            id += cHUMIDITY;
            break;
        case VARIABLE_TYPE_RAIN:
            cRAIN++;
            id += cRAIN;
            break;
        case VARIABLE_TYPE_WIND_SPEED:
            cWIND_SPEED++;
            id += cWIND_SPEED;
            break;
        case VARIABLE_TYPE_WIND_DIRECTION:
            cWIND_DIRECTION++;
            id += cWIND_DIRECTION;
            break;
        case VARIABLE_TYPE_PREASSURE:
            cPREASSURE++;
            id += cPREASSURE;
            break;
        case VARIABLE_TYPE_VAPOR_PRESURE:
            cVAPOR_PRESURE++;
            id += cVAPOR_PRESURE;
            break;
        case VARIABLE_TYPE_PAR_RADIATION:
            cPAR_RADIATION++;
            id += cPAR_RADIATION;
            break;
        case VARIABLE_TYPE_UV_RADIATION:
            cUV_RADIATION++;
            id += cUV_RADIATION;
            break;
        case VARIABLE_TYPE_IRR_RADIATION:
            cIRR_RADIATION++;
            id += cIRR_RADIATION;
            break;
        case VARIABLE_TYPE_PH:
            cPH++;
            id += cPH;
            break;
        case VARIABLE_TYPE_EC:
            cEC++;
            id += cEC;
            break;
        case VARIABLE_TYPE_SOIL_TEMPERATURE:
            cSOIL_TEMPERATURE++;
            id += cSOIL_TEMPERATURE;
            break;
        case VARIABLE_TYPE_SOIL_HUMIDITY:
            cSOIL_HUMIDITY++;
            id += cSOIL_HUMIDITY;
            break;
        case VARIABLE_TYPE_WATER_POTENTIAL:
            cWATER_POTENTIAL++;
            id += cWATER_POTENTIAL;
            break;
        case VARIABLE_TYPE_SOIL_SALINITY:
            cSOIL_SALINITY++;
            id += cSOIL_SALINITY;
            break;
        case VARIABLE_TYPE_LEAF_HUMIDITY:
            cLEAF_HUMIDITY++;
            id += cLEAF_HUMIDITY;
            break;
        case VARIABLE_TYPE_LEAF_TEMPERATURE:
            cLEAF_TEMPERATURE++;
            id += cLEAF_TEMPERATURE;
            break;
        }

        Variable_t variable = {id, type, 0};
        return variable;
    }
};

#endif  // __REGISTERS_VARIABLE_REGISTER_H
