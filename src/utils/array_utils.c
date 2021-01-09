#include "array_utils.h"

uint8_t clear_array(void *buff, uint16_t _bytes_len)
{
    if (buff == NULL)
        return POINTER_IS_NULL;
    uint8_t *ptr = (uint8_t *)buff;
    for (uint16_t i = 0; i < _bytes_len; i++)
    {
        ptr = 0x00;
        ptr++;
    }
    return NO_ERROR;
}

uint8_t reverse_array(uint8_t *buff, uint16_t len)
{
    if (buff == NULL)
        return POINTER_IS_NULL;

    int c, t;

    for (c = 0; c < len / 2; c++)
    {
        t = buff[c];  // Swapping
        buff[c] = buff[len - c - 1];
        buff[len - c - 1] = t;
    }
    return NO_ERROR;
}