#if !defined(__SENSORS_MODBUS_RTU_PARSE_H)
#define __SENSORS_MODBUS_RTU_PARSE_H

#include <stdint.h>

#include "utils/linked_list.h"
#include "utils/linked_list_utils.h"

uint16_t ParseSingleRegisterCommand(uint8_t *rx_buffer, uint8_t rx_len);

LinkedList<uint16_t> ParseMultiRegisterCommand(uint8_t *rx_buffer, uint8_t rx_len);

#endif  // __SENSORS_MODBUS_RTU_PARSE_H
