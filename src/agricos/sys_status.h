#if !defined(AGRICOS_SYS_STATUS_H)
#define AGRICOS_SYS_STATUS_H

#include "common.h"

typedef struct
{
    Time_s sysTime;
    eRtcMode_t sysRtcMode;

    uint32_t sysMilliseconds;
    uint32_t suceessMeasures;
    uint32_t measuresTaked;
} AgricosCore_Status_t;

#endif  // AGRICOS_SYS_STATUS_H
