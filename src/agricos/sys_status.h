#if !defined(AGRICOS_SYS_STATUS_H)
#define AGRICOS_SYS_STATUS_H

#include "common.h"

typedef struct
{
    Time_s sysTime;
    uint32_t sysMilliseconds;
    uint32_t suceessMeasures;
} AgricosCore_Status;

#endif  // AGRICOS_SYS_STATUS_H
