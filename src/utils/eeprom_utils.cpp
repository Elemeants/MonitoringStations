#include "eeprom_utils.h"

#include "logger/ikernel_logger.h"
#include "utils/linked_list_utils.h"

EEPROM_Result_e ee_write(uint8_t byte, uint8_t addr)
{
    if (addr > 255U)
    {
        return EEPROM_INDEX_OUT_RANGE;
    }
#if __EEPROM_INVERTING_LOGIC
    EEPROM.write(addr, ~byte);
#else
    EEPROM.write(addr, byte);
#endif
    return EEPROM_NO_ERROR;
}

EEPROM_Result_e ee_write_buffer(uint8_t addr, uint8_t *buff, uint8_t len)
{
    if (buff == NULL)
    {
        return EEPROM_BUFFER_NULL;
    }
    if (len == 0U)
    {
        return EEPROM_BUFFER_EMPTY;
    }
    if (addr > 255U)
    {
        return EEPROM_INDEX_OUT_RANGE;
    }
    for_in_range(uint8_t, i, 0U, len)
    {
        ee_write(buff[i], addr + i);
    }
    return EEPROM_NO_ERROR;
}

EEPROM_Result_e ee_write_string(uint8_t addr, const char *str, uint16_t len)
{
    char *buff = (char *)str;
    uint8_t buff_len = len;
    return ee_write_buffer(addr, (uint8_t *)buff, buff_len);
}

EEPROM_Result_e ee_write_string(uint8_t addr, String str)
{
    char *buff = (char *)str.c_str();
    uint8_t buff_len = str.length();
    return ee_write_buffer(addr, (uint8_t *)buff, buff_len);
}

uint8_t ee_read(uint8_t addr)
{
    if (addr > 255U)
    {
        return EEPROM_INDEX_OUT_RANGE;
    }
#if __EEPROM_INVERTING_LOGIC
    return ~EEPROM.read(addr);
#else
    return EEPROM.read(addr);
#endif
}

EEPROM_Result_e ee_read_buffer(uint8_t addr, uint8_t *buff, uint8_t len)
{
    if (buff == NULL)
    {
        return EEPROM_BUFFER_NULL;
    }
    if (len == 0)
    {
        return EEPROM_BUFFER_EMPTY;
    }
    if (addr > 255)
    {
        return EEPROM_INDEX_OUT_RANGE;
    }
    for_in_range(uint8_t, i, 0U, len)
    {
        uint8_t val = ee_read(addr + i);
        buff[i] = val;
        if (val == 13U)
        {
            break;
        }
    }
    return EEPROM_NO_ERROR;
}

String ee_read_string(uint8_t addr, uint8_t len)
{
    char buffer[len];
    ee_read_buffer(addr, (uint8_t *)buffer, len);
#if DEBUG_EEPRON
    dump_eeprom_region(addr, addr + len);
#endif
    return String(buffer);
}

void dump_eeprom_mem()
{
    char buffer[6];
    logger.log(F("---------- Dumping EEPROM ----------"), LOG_DEBUG);
    for_in_range(uint8_t, i, __EEPROM_START_ADDR, __EEPROM_END_ADDR)
    {
        sprintf(buffer, "0x%02X", ee_read(i));
        logger << buffer << F(" ");
        if (i % 16U == 0U)
        {
            sprintf(buffer, "%04u", i);
            logger << EndLine << LOG_DEBUG << F(" ") << buffer << F(": ");
        }
    }
    logger << EndLine;
}

void dump_eeprom_region(uint8_t __in, uint8_t __end)
{
    char buffer[6];
    logger.log(F("---------- Dumping Region ----------"), LOG_DEBUG);
    for_in_range(uint8_t, i, __in, __end)
    {
        sprintf(buffer, "0x%02X", ee_read(i));
        logger << buffer << F(" ");
        if (i % 16U == 0U)
        {
            sprintf(buffer, "%04u", i);
            logger << EndLine << LOG_DEBUG << F(" ") << buffer << F(": ");
        }
    }
    logger << EndLine;
}

void reset_eeprom()
{
    for_in_range(uint8_t, i, __EEPROM_START_ADDR, __EEPROM_END_ADDR)
    {
        ee_write(0x00U, i);
    }
}