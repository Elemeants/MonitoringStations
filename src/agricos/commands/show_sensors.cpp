#include "../globals.h"
#include "../sensors.h"
#include "cmd.h"
#include "common.h"

static char table_buffer[65];

static void AgricosCli_CMD_ShowSensors(cmd *_)
{
    Command cmd(_);
    logger << LOG_MASTER << F(" --------------------> Sensors Registrated <--------------------") << EndLine;
    logger << LOG_MASTER << F(" | ID              | PROTOCOL |           VARIABLES            |") << EndLine;
    logger << LOG_MASTER << F(" ---------------------------------------------------------------") << EndLine;

    for_in_range(auto, i, 0, StationSensors.size())
    {
        SensorInfo_t *info = StationSensors.get(i);
        if (!info)
        {
            continue;
        }
        String protocol = SensorProtocolToStr(info->protocol);
        snprintf(table_buffer, array_size(table_buffer), " | %15s | %8s | ", info->id, protocol.c_str());
        logger << LOG_MASTER << table_buffer;

        uint16_t c_s = 0;
        for_in_range(uint8_t, j, 0, info->variables.size())
        {
            Variable_t var = info->variables[j];
            String var_name = VariableTypeToStr(var.type);
            c_s += var_name.length();
            logger << var_name;

            if (c_s >= 26)  // 30 buffer size - 4 char space
            {
                logger << EndLine << LOG_MASTER << F(" |                 |          | ");
                continue;
            }

            if (i < info->variables.size() - 1)
            {
                logger << F(", ");
                c_s += 2;
            }
        }
    }
}

void AgricosCli_Add_ShowSensors()
{
    Command cmd = AgricosCli.addCommand("sensors", AgricosCli_CMD_ShowSensors);
    cmd.setCaseSensetive(true);
    cmd.setDescription(" Shows all sensors registered");
}