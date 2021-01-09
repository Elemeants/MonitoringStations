#if !defined(REGISTERS_JSON_MEASURE_REGISTER_H)
#define REGISTERS_JSON_MEASURE_REGISTER_H

#include <ArduinoJson.h>

#include "common.h"
#include "config_provider.h"

#define JSON_STATIC_RAM_SIZE 1024

extern StaticJsonDocument<JSON_STATIC_RAM_SIZE> jsonFileRoot;
extern char JSON_SERIALIZED_BUFFER[JSON_STATIC_RAM_SIZE];

struct _JsonMeasureRegister : _MeasureRegister
{
private:
    JsonArray measures;

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

    bool addMeasure(Variable_t &variable)
    {
        JsonObject aux = measures.createNestedObject();
        aux["v"] = variable.measure;
        aux["m"] = variable.id;
        return true;
    }

    void init()
    {
        jsonFileRoot.clear();
        JsonArray deviceList = jsonFileRoot.createNestedArray("d");
        JsonObject device = deviceList.createNestedObject();
        device["k"] = Configuration::DeviceCode;

        measures = device.createNestedArray(F("m"));
    }

    void clear()
    {
        jsonFileRoot.clear();
    }

    void serialize()
    {
        serializeJson(jsonFileRoot, JSON_SERIALIZED_BUFFER);
    }
};

#endif  // REGISTERS_JSON_MEASURE_REGISTER_H
