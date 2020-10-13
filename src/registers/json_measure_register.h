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

    template <typename T>
    bool _addMeasure(T &val, const __FlashStringHelper *code)
    {
        JsonObject aux = measures.createNestedObject();
        aux["v"] = val;
        aux["m"] = code;
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

    bool addMeasure(bool &value, const __FlashStringHelper *code) { return _addMeasure(value, code); }
    bool addMeasure(float &value, const __FlashStringHelper *code) { return _addMeasure(value, code); }
    bool addMeasure(double &value, const __FlashStringHelper *code) { return _addMeasure(value, code); }
    bool addMeasure(signed char &value, const __FlashStringHelper *code) { return _addMeasure(value, code); }
    bool addMeasure(signed long &value, const __FlashStringHelper *code) { return _addMeasure(value, code); }
    bool addMeasure(signed int &value, const __FlashStringHelper *code) { return _addMeasure(value, code); }
    bool addMeasure(signed short &value, const __FlashStringHelper *code) { return _addMeasure(value, code); }
    bool addMeasure(unsigned char &value, const __FlashStringHelper *code) { return _addMeasure(value, code); }
    bool addMeasure(unsigned long &value, const __FlashStringHelper *code) { return _addMeasure(value, code); }
    bool addMeasure(unsigned int &value, const __FlashStringHelper *code) { return _addMeasure(value, code); }
    bool addMeasure(unsigned short &value, const __FlashStringHelper *code) { return _addMeasure(value, code); }
    bool addMeasure(const char *value, const __FlashStringHelper *code) { return _addMeasure(value, code); }
    bool addMeasure(char *value, const __FlashStringHelper *code) { return _addMeasure(value, code); }

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
