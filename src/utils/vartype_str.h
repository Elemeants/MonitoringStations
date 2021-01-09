#if !defined(__UTILS_VARIABLE_TYPE_TO_STR_H)
#define __UTILS_VARIABLE_TYPE_TO_STR_H

#include <Arduino.h>

#include "../types/variable_types.h"

const __FlashStringHelper *VariableTypeToCode(VariableType_e type);
const __FlashStringHelper *VariableTypeToStr(VariableType_e type);

#endif  // __UTILS_VARIABLE_TYPE_TO_STR_H
