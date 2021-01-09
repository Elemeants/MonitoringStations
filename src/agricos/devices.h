#if !defined(AGRICOS_DEVICES_H)
#define AGRICOS_DEVICES_H

#include <devices/include.h>

#include "board.h"
#include "config.h"

extern ITimeProvider *TimeProvider;

extern void AgricosDevices_Init(void);

#endif  // AGRICOS_DEVICES_H
