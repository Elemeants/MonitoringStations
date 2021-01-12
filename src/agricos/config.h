#if !defined(AGRICOS_CONFIG_H)
#define AGRICOS_CONFIG_H

#include "stations/selector.h"

// System Developer
#define PROGRAMMER_NAME "Daniel Polanco"

// Firmware AgricOS
#define FIRMWARE_VERSION "v3.0.1"

// Compilation firmware status
#define COMPILATION_VERSION FIRMWARE_VERSION "." __TIME__ "." __DATE__

// Board version
// 300: Version 3.00 # NO IMPLEMENTED
// 210: Version 2.10
// 200: Version 2.00
// 000: No board specific version
#define BOARD_VERSION 210

// Agricos Station Target
// The available station versios are in station/selector.h
#define AGRICOS_STATION_TARGET CROPFIELD_POMAS_ES003

#endif  // AGRICOS_CONFIG_H
