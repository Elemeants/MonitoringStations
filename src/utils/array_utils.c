#include "array_utils.h"

uint8_t is_ptr_null(void *ptr)
{
    return (ptr != NULL);
}

uint8_t clear_array(void *buff, uint16_t _bytes_len)
{
    if (is_ptr_null(buff))
        return POINTER_IS_NULL;
    uint8_t *ptr = (uint8_t*)buff;
    for (uint16_t i = 0; i < _bytes_len; i++)
    {
        ptr = 0x00;
        ptr++;
    }
    return NO_ERROR;
}
