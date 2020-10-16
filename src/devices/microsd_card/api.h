#if !defined(MICROSD_CARD_API_H)
#define MICROSD_CARD_API_H

#include <stdint.h>

#include "driver/SD.h"

bool MicroSD_Init(uint8_t cs_pin);
bool MicroSD_CreateDir(char *name);
File MicroSD_CreateFile(char *name);

bool MicroSD_WriteToFile(File, char *data, uint32_t len);
bool MicroSD_ReadFromFile(File, char *buffer, uint32_t len);

uint32_t MicroSD_CountFiles(char *folderName);

#endif  // MICROSD_CARD_API_H
