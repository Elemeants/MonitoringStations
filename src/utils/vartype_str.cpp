#include "vartype_str.h"

const __FlashStringHelper *VariableTypeToCode(VariableType_e type)
{
    switch (type)
    {
    case VARIABLE_TYPE_BATTERY:
        return F("bt");
    case VARIABLE_TYPE_TEMPERATURE:
        return F("th");
    case VARIABLE_TYPE_HUMIDITY:
        return F("");
    case VARIABLE_TYPE_RAIN:
        return F("");
    case VARIABLE_TYPE_WIND_SPEED:
        return F("");
    case VARIABLE_TYPE_WIND_DIRECTION:
        return F("");
    case VARIABLE_TYPE_PREASSURE:
        return F("");
    case VARIABLE_TYPE_VAPOR_PRESURE:
        return F("");
    case VARIABLE_TYPE_PAR_RADIATION:
        return F("");
    case VARIABLE_TYPE_UV_RADIATION:
        return F("");
    case VARIABLE_TYPE_IRR_RADIATION:
        return F("");
    case VARIABLE_TYPE_PH:
        return F("");
    case VARIABLE_TYPE_EC:
        return F("");
    case VARIABLE_TYPE_SOIL_TEMPERATURE:
        return F("");
    case VARIABLE_TYPE_SOIL_HUMIDITY:
        return F("");
    case VARIABLE_TYPE_WATER_POTENTIAL:
        return F("");
    case VARIABLE_TYPE_LEAF_HUMIDITY:
        return F("");
    default:
        return F("");
    }
}

const __FlashStringHelper *VariableTypeToStr(VariableType_e type)
{
    switch (type)
    {
    case VARIABLE_TYPE_BATTERY:
        return F("Battery");
    case VARIABLE_TYPE_TEMPERATURE:
        return F("Temperature");
    case VARIABLE_TYPE_HUMIDITY:
        return F("Humidity");
    case VARIABLE_TYPE_RAIN:
        return F("Rain");
    case VARIABLE_TYPE_WIND_SPEED:
        return F("Wind speed");
    case VARIABLE_TYPE_WIND_DIRECTION:
        return F("Wind direction");
    case VARIABLE_TYPE_PREASSURE:
        return F("Preassure");
    case VARIABLE_TYPE_VAPOR_PRESURE:
        return F("Vapor preassure");
    case VARIABLE_TYPE_PAR_RADIATION:
        return F("PAR Radiation");
    case VARIABLE_TYPE_UV_RADIATION:
        return F("UV Radiation");
    case VARIABLE_TYPE_IRR_RADIATION:
        return F("IRR Radiation");
    case VARIABLE_TYPE_PH:
        return F("pH");
    case VARIABLE_TYPE_EC:
        return F("Ec");
    case VARIABLE_TYPE_SOIL_TEMPERATURE:
        return F("Soil temp");
    case VARIABLE_TYPE_SOIL_HUMIDITY:
        return F("Soil humidity");
    case VARIABLE_TYPE_WATER_POTENTIAL:
        return F("Water potential");
    case VARIABLE_TYPE_LEAF_HUMIDITY:
        return F("Leaf humidity");
    case VARIABLE_TYPE_SOIL_SALINITY:
        return F("Salinity");
    default:
        return F("Not assigned");
    }
}
