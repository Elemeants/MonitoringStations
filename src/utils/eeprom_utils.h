#if !defined(EEPROM_UTILS_H)
#define EEPROM_UTILS_H

#include <EEPROM.h>
#include <stdint.h>

#define __EEPROM_START_ADDR 0x00
#define __EEPROM_END_ADDR 0xFF

#define __EEPROM_INVERTING_LOGIC 0

typedef enum
{
    EEPROM_NO_ERROR = 0,
    EEPROM_INDEX_OUT_RANGE = 255,
    EEPROM_BUFFER_NULL = 254,
    EEPROM_BUFFER_EMPTY = 253
} EEPROM_Result_e;

EEPROM_Result_e ee_write(uint8_t byte, uint8_t addr);
EEPROM_Result_e ee_write_buffer(uint8_t addr, uint8_t *buff, uint8_t len);
EEPROM_Result_e ee_write_string(uint8_t addr, const char *str, uint16_t len);

class String;
EEPROM_Result_e ee_write_string(uint8_t addr, String str);

uint8_t ee_read(uint8_t addr);
EEPROM_Result_e ee_read_buffer(uint8_t addr, uint8_t *buff, uint8_t len);
String ee_read_string(uint8_t addr, uint8_t len);

void reset_eeprom();

void dump_eeprom_mem();
void dump_eeprom_region(uint8_t __in, uint8_t __end);

#endif  // EEPROM_UTILS_H
