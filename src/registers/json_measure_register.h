#if !defined(REGISTERS_JSON_MEASURE_REGISTER_H)
#define REGISTERS_JSON_MEASURE_REGISTER_H

#include <ArduinoJson.h>

#include "measure_register.h"

#define JSON_STATIC_RAM_SIZE 512

extern StaticJsonDocument<JSON_STATIC_RAM_SIZE> jsonFileRoot;

struct _JsonMeasureRegister : _MeasureRegister
{
private:
    JsonArray measures;

    const __FlashStringHelper *VariableTypeCode(VariableType_e type)
    {
        switch (type)
        {
        case VARIABLE_TYPE_BATTERY:
            return F("");
        case VARIABLE_TYPE_TEMPERATURE:
            return F("");
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

    template <typename T>
    bool _addMeasure(T &val, VariableType_e type)
    {
        JsonObject aux = measures.createNestedObject();
        aux["v"] = val;
        aux["m"] = VariableTypeCode(type);
        return true;
    }

    template <typename T>
    bool _addAttribute(T &val, const __FlashStringHelper *code)
    {
        jsonFileRoot[code] = val;
        return true;
    }

public:
    _JsonMeasureRegister()
        : _MeasureRegister()
    {
    }

    bool addAttribute(bool &value, const __FlashStringHelper *code) { return _addAttribute(value, code); }
    bool addAttribute(float &value, const __FlashStringHelper *code) { return _addAttribute(value, code); }
    bool addAttribute(double &value, const __FlashStringHelper *code) { return _addAttribute(value, code); }
    bool addAttribute(signed char &value, const __FlashStringHelper *code) { return _addAttribute(value, code); }
    bool addAttribute(signed long &value, const __FlashStringHelper *code) { return _addAttribute(value, code); }
    bool addAttribute(signed int &value, const __FlashStringHelper *code) { return _addAttribute(value, code); }
    bool addAttribute(signed short &value, const __FlashStringHelper *code) { return _addAttribute(value, code); }
    bool addAttribute(unsigned char &value, const __FlashStringHelper *code) { return _addAttribute(value, code); }
    bool addAttribute(unsigned long &value, const __FlashStringHelper *code) { return _addAttribute(value, code); }
    bool addAttribute(unsigned int &value, const __FlashStringHelper *code) { return _addAttribute(value, code); }
    bool addAttribute(unsigned short &value, const __FlashStringHelper *code) { return _addAttribute(value, code); }
    bool addAttribute(const char *value, const __FlashStringHelper *code) { return _addAttribute(value, code); }
    bool addAttribute(char *value, const __FlashStringHelper *code) { return _addAttribute(value, code); }

    bool addMeasure(bool &value, VariableType_e type) { return _addMeasure(value, type); }
    bool addMeasure(float &value, VariableType_e type) { return _addMeasure(value, type); }
    bool addMeasure(double &value, VariableType_e type) { return _addMeasure(value, type); }
    bool addMeasure(signed char &value, VariableType_e type) { return _addMeasure(value, type); }
    bool addMeasure(signed long &value, VariableType_e type) { return _addMeasure(value, type); }
    bool addMeasure(signed int &value, VariableType_e type) { return _addMeasure(value, type); }
    bool addMeasure(signed short &value, VariableType_e type) { return _addMeasure(value, type); }
    bool addMeasure(unsigned char &value, VariableType_e type) { return _addMeasure(value, type); }
    bool addMeasure(unsigned long &value, VariableType_e type) { return _addMeasure(value, type); }
    bool addMeasure(unsigned int &value, VariableType_e type) { return _addMeasure(value, type); }
    bool addMeasure(unsigned short &value, VariableType_e type) { return _addMeasure(value, type); }
    bool addMeasure(const char *value, VariableType_e type) { return _addMeasure(value, type); }
    bool addMeasure(char *value, VariableType_e type) { return _addMeasure(value, type); }

    void init()
    {
        jsonFileRoot.clear();
        JsonArray deviceList = jsonFileRoot.createNestedArray("d");
        JsonObject device = deviceList.createNestedObject();
        device["k"] = "ES001";

        measures = device.createNestedArray(F("m"));
    }

    void clear()
    {
        jsonFileRoot.clear();
    }
};

#endif  // REGISTERS_JSON_MEASURE_REGISTER_H
