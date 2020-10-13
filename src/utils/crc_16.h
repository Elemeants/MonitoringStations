#if !defined(MODBUS_CRC16_H)
#define MODBUS_CRC16_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif  // __cplusplus
    uint16_t calculate_crc16(uint8_t *data, uint8_t len);
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // MODBUS_CRC16_H
