#if !defined(AGRICOS_CORE_BOARD_H)
#define AGRICOS_CORE_BOARD_H

#include "config.h"

// ============ Configuration for board version 2.10
#if BOARD_VERSION == 210
#include "boards/board_v210.h"
// ============ Configuration for board version 2.00
#elif BOARD_VERSION == 200
#include "boards/board_v200.h"
#endif

#endif // AGRICOS_CORE_BOARD_H
