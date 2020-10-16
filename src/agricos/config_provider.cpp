#include "config_provider.h"

/* -----------------------------------------------------------------------
 *                        EEPROM REGION CONFIGURATION
 * -----------------------------------------------------------------------
 * [0x00, 0x09]: Station code
 * [0x0A, 0x6D]: Url server to post
 * [0x6E, 0x7F]: Modules enabled
 *          (For Agricos v2)
 *          0x6E -> ModuleRtc
 *          0x6F -> ModuleDavisAnenometer
 *          0x70 -> ModuleSdCard
 *          0x71 -> ModuleMeter
 *          0x72 -> ModuleBattery
 *          0x73 -> ModuleSHT1X
 *          0x74 -> ModulePluviometer
 *          0x75 -> ModuleAnenometer
 *          0x76 -> ModuleAtlas
 *          0x77 -> ModuleApogee
 *          0x78 -> ModuleBarometer
 *          0x79 -> ModuleGps
 *          0x7A -> ModuleGprs
 *          0x7B -> RESERVED
 *          0x7C -> RESERVED
 *          0x7D -> RESERVED
 *          0x7E -> RESERVED
 *          0x7F -> RESERVED
 * [0x80, 0x80]: Kernel config
 *          0x80[2:0] -> RTC mode
 *          0x80[3]   -> Adjust RTC
 *          0x80[7:4] -> Logger mode
 * [0x81, 0x86]: Adjust Time struct
 *          0x81 -> year
 *          0x82 -> month
 *          0x83 -> day
 *          0x84 -> hour
 *          0x85 -> minute
 *          0x86 -> second
 * -----------------------------------------------------------------------
*/

char Configuration::DeviceCode[DEVICE_CODE_LENGHT];
char Configuration::ServerUrl[SERVER_URL_LENGHT];

static uint8_t OFFSET_MODULE_ENABLED = 0x6E;
static uint8_t OFFSET_LOG_RTC_CONFIG = 0x80;
static uint8_t OFFSET_TIME_CONFIG = 0x81;

bool Configuration::isModuleEnabled(uint8_t module)
{
    return ee_read(module + OFFSET_MODULE_ENABLED);
}

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
    return (eLogLevel_t)(ee_read(OFFSET_LOG_RTC_CONFIG) >> 0x4);
}

void storeLogLevel(eLogLevel_t mode)
{
    uint8_t mask = ee_read(OFFSET_LOG_RTC_CONFIG) & 0b1111;
    mask |= (((uint8_t)mode & 0b1111) << 4);
    ee_write(OFFSET_LOG_RTC_CONFIG, mask);
}

uint8_t Configuration::readRTCMode()
{
    return ee_read(OFFSET_LOG_RTC_CONFIG) & 0b0111;
}

void storeRTCMode(uint8_t mode)
{
    uint8_t mask = ee_read(OFFSET_LOG_RTC_CONFIG) & (0b11111 << 4);
    mask |= (mode & 0b111);
    ee_write(OFFSET_LOG_RTC_CONFIG, mask);
}

uint8_t Configuration::isAdjustRTCEnabled()
{
    return ee_read(OFFSET_LOG_RTC_CONFIG) & 0b1000;
}

Time_s Configuration::readAdjustTime()
{
    Time_s stored_time(0, 0, 0, 0, 0, 0);
    stored_time.year = 2000U + ee_read(OFFSET_TIME_CONFIG);
    stored_time.month = ee_read(OFFSET_TIME_CONFIG + 0x1);
    stored_time.day = ee_read(OFFSET_TIME_CONFIG + 0x2);
    stored_time.hour = ee_read(OFFSET_TIME_CONFIG + 0x3);
    stored_time.minute = ee_read(OFFSET_TIME_CONFIG + 0x4);
    stored_time.second = ee_read(OFFSET_TIME_CONFIG + 0x5);
    return stored_time;
}

void Configuration::printConfiguration()
{
    logger << LOG_MASTER << F(" Station stored configuration") << EndLine;
    logger << LOG_MASTER << F("     ├── Station code: ") << Configuration::DeviceCode << EndLine;
    logger << LOG_MASTER << F("     ├── Url server: ") << Configuration::ServerUrl << EndLine;
    logger << LOG_MASTER << F("     ├── Log Mode: ") << (uint8_t)Configuration::readLogLevel() << EndLine;
    logger << LOG_MASTER << F("     ├── RTC Mode: ") << Configuration::readRTCMode() << EndLine;
    logger << LOG_MASTER << F("     └── Adjust RTC: ") << (bool)Configuration::isAdjustRTCEnabled() << EndLine;
}

void Configuration::init()
{
    Configuration::readStationCode();
    Configuration::readUrlServer();
    Configuration::printConfiguration();
}