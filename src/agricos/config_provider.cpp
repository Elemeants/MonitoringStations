#include "config_provider.h"

#include "config.h"

/* -----------------------------------------------------------------------
 *                        EEPROM REGION CONFIGURATION
 * -----------------------------------------------------------------------
 * [0x00, 0x09]: Station code
 * [0x0A, 0x6D]: Url server to post
 * [0x6E]: RTC mode
 * [0x6F]: Logger mode
 * [0x70]: Lat manually
 * [0x71]: Lng manually
 * -----------------------------------------------------------------------
*/

char Configuration::DeviceCode[DEVICE_CODE_LENGHT];
char Configuration::ServerUrl[SERVER_URL_LENGHT];

float Configuration::DeviceLat;
float Configuration::DeviceLng;

static uint8_t OFFSET_RTC_CONFIG = 0x6E;
static uint8_t OFFSET_LOG_CONFIG = 0x6F;
static uint8_t OFFSET_LAT_CONFIG = 0x70;
static uint8_t OFFSET_LNG_CONFIG = OFFSET_LAT_CONFIG + sizeof(float) + 1U;

void Configuration::readStationCode()
{
    uint8_t *buffer = (uint8_t *)Configuration::DeviceCode;
    uint8_t len = array_size(Configuration::DeviceCode);
    ee_read_buffer(0x00, buffer, len);
}

void Configuration::readUrlServer()
{
    uint8_t *buffer = (uint8_t *)Configuration::ServerUrl;
    uint8_t len = array_size(Configuration::ServerUrl);
    ee_read_buffer(0x0A, buffer, len);
}

void Configuration::updateStationCode()
{
    uint8_t *buffer = (uint8_t *)Configuration::DeviceCode;
    uint8_t len = array_size(Configuration::DeviceCode);
    for_in_range(uint8_t, i, 0, len)
    {
        ee_write(0x00, i);
    }
    ee_write_buffer(0x00, buffer, len);
}

void Configuration::updateUrlServer()
{
    uint8_t *buffer = (uint8_t *)Configuration::ServerUrl;
    uint8_t len = array_size(Configuration::ServerUrl);
    for_in_range(uint8_t, i, 0x0A, len + 0x0A)
    {
        ee_write(0x00, i);
    }
    ee_write_buffer(0x0A, buffer, len);
}

eLogLevel_t Configuration::readLogLevel()
{
    return (eLogLevel_t)(ee_read(OFFSET_LOG_CONFIG));
}

void Configuration::storeLogLevel(eLogLevel_t mode)
{
    ee_write((uint8_t)mode, OFFSET_LOG_CONFIG);
}

uint8_t Configuration::readRTCMode()
{
    return ee_read(OFFSET_RTC_CONFIG);
}

void Configuration::storeRTCMode(uint8_t mode)
{
    ee_write(mode, OFFSET_RTC_CONFIG);
}

void Configuration::readGPSLat()
{
    uint8_t *buffer = (uint8_t *)&Configuration::DeviceLat;
    uint8_t len = sizeof(float);
    ee_read_buffer(OFFSET_LAT_CONFIG, buffer, len);
    reverse_array(buffer, len);  // We store the value as big endian so we reverse it for little endian
}

void Configuration::updadteGPSLat(float lat)
{
    uint8_t *buffer = (uint8_t *)&Configuration::DeviceLat;
    uint8_t len = sizeof(float);
    ee_write_buffer(OFFSET_LAT_CONFIG, buffer, len);
}

void Configuration::readGPSLng()
{
    uint8_t *buffer = (uint8_t *)&Configuration::DeviceLng;
    uint8_t len = sizeof(float);
    ee_read_buffer(OFFSET_LNG_CONFIG, buffer, len);
    reverse_array(buffer, len);  // We store the value as big endian so we reverse it for little endian
}

void Configuration::updadteGPSLng(float lng)
{
    uint8_t *buffer = (uint8_t *)&Configuration::DeviceLng;
    uint8_t len = sizeof(float);
    ee_write_buffer(OFFSET_LNG_CONFIG, buffer, len);
}

const __FlashStringHelper *LogLevelToStr(eLogLevel_t log_lv)
{
    switch (log_lv)
    {
    case LOG_DEBUG:
        return F("\033[1m\033[35mDEBUG\033[0m");
    case LOG_INFO:
        return F("\033[1m\033[32mINFO\033[0m");
    case LOG_WARN:
        return F("\033[1m\033[93mWARN\033[0m");
    case LOG_ERROR:
        return F("\033[1m\033[91mERROR\033[0m");
    default:
        return F("Unknow");
    }
}

void Configuration::printConfiguration()
{
    logger << LOG_MASTER << F(" Station stored configuration") << EndLine;
    logger << LOG_MASTER << F("     ├-- Compilation:    ") << LOGGER_TEXT_YELLOW << COMPILATION_VERSION << EndLine;
    logger << LOG_MASTER << F("     ├-- Board code:     ") << LOGGER_TEXT_YELLOW << BOARD_VERSION << EndLine;
    logger << LOG_MASTER << F("     ├-- Station code:   ") << LOGGER_TEXT_YELLOW << Configuration::DeviceCode << EndLine;
    logger << LOG_MASTER << F("     ├-- Url server:     ") << LOGGER_TEXT_YELLOW << Configuration::ServerUrl << EndLine;
    logger << LOG_MASTER << F("     ├-- Log Mode:       ") << LOGGER_TEXT_YELLOW << LogLevelToStr(Configuration::readLogLevel()) << EndLine;
    logger << LOG_MASTER << F("     └-- RTC Mode:       ") << LOGGER_TEXT_YELLOW << GetStringRtcMode((RTCMode_e)Configuration::readRTCMode()) << EndLine;
}

void Configuration::init()
{
    EEPROM.begin();
    Configuration::readStationCode();
    Configuration::readUrlServer();
    Configuration::printConfiguration();
}