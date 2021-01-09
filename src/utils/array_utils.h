#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <stdint.h>
#include <stdlib.h>

#include "error_codes.h"

#define array_size(arr) (sizeof(arr) / sizeof(arr[0]))

#ifdef __cplusplus
extern "C"
{
#endif  // __cplusplus
    uint8_t clear_array(void *buff, uint16_t len);
    uint8_t reverse_array(uint8_t *buff, uint16_t len);
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // !ARRAY_UTILS_H