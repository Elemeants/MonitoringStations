#if !defined(AGRICOS_CONFIG_PROVIDER_H)
#define AGRICOS_CONFIG_PROVIDER_H

#include "common.h"

#define DEVICE_CODE_LENGHT 10
#define SERVER_URL_LENGHT 100

namespace Configuration
{
extern char DeviceCode[DEVICE_CODE_LENGHT];
extern char ServerUrl[SERVER_URL_LENGHT];

void printConfiguration();
void init();

bool isModuleEnabled(uint8_t module);

void readStationCode();
void readUrlServer();

void updateStationCode();
void updateUrlServer();

eLogLevel_t readLogLevel();
void storeLogLevel(eLogLevel_t level);

uint8_t readRTCMode();
void storeRTCMode(uint8_t mode);

uint8_t isAdjustRTCEnabled();
Time_s readAdjustTime();
}  // namespace Configuration

#endif  // AGRICOS_CONFIG_PROVIDER_H
