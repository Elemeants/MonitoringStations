#if !defined(REGISTERS_MEASURE_REGISTER_H)
#define REGISTERS_MEASURE_REGISTER_H

#include <Arduino.h>
#include "types/register.h"
#include "utils/linked_list_utils.h"

class _MeasureRegister
{
public:
  _MeasureRegister()
  {
  }

  virtual void init() {}
  virtual void clear() {}

  virtual bool addAttribute(bool &value, const __FlashStringHelper *code) = 0;
  virtual bool addAttribute(float &value, const __FlashStringHelper *code) = 0;
  virtual bool addAttribute(double &value, const __FlashStringHelper *code) = 0;
  virtual bool addAttribute(signed char &value, const __FlashStringHelper *code) = 0;
  virtual bool addAttribute(signed long &value, const __FlashStringHelper *code) = 0;
  virtual bool addAttribute(signed int &value, const __FlashStringHelper *code) = 0;
  virtual bool addAttribute(signed short &value, const __FlashStringHelper *code) = 0;
  virtual bool addAttribute(unsigned char &value, const __FlashStringHelper *code) = 0;
  virtual bool addAttribute(unsigned long &value, const __FlashStringHelper *code) = 0;
  virtual bool addAttribute(unsigned int &value, const __FlashStringHelper *code) = 0;
  virtual bool addAttribute(unsigned short &value, const __FlashStringHelper *code) = 0;
  virtual bool addAttribute(const char *value, const __FlashStringHelper *code) = 0;
  virtual bool addAttribute(char *value, const __FlashStringHelper *code) = 0;

  virtual bool addMeasure(bool &value, const __FlashStringHelper *code) = 0;
  virtual bool addMeasure(float &value, const __FlashStringHelper *code) = 0;
  virtual bool addMeasure(double &value, const __FlashStringHelper *code) = 0;
  virtual bool addMeasure(signed char &value, const __FlashStringHelper *code) = 0;
  virtual bool addMeasure(signed long &value, const __FlashStringHelper *code) = 0;
  virtual bool addMeasure(signed int &value, const __FlashStringHelper *code) = 0;
  virtual bool addMeasure(signed short &value, const __FlashStringHelper *code) = 0;
  virtual bool addMeasure(unsigned char &value, const __FlashStringHelper *code) = 0;
  virtual bool addMeasure(unsigned long &value, const __FlashStringHelper *code) = 0;
  virtual bool addMeasure(unsigned int &value, const __FlashStringHelper *code) = 0;
  virtual bool addMeasure(unsigned short &value, const __FlashStringHelper *code) = 0;
  virtual bool addMeasure(const char *value, const __FlashStringHelper *code) = 0;
  virtual bool addMeasure(char *value, const __FlashStringHelper *code) = 0;
};

#endif // REGISTERS_MEASURE_REGISTER_H
