#include "api.h"

#include <string.h>

#include "common.h"

bool MicroSD_Init(uint8_t cs_pin)
{
    logger << LOG_INFO << F("          └-- Initializing MicroSD Card...") << EndLine;
    if (SD.begin(cs_pin))
    {
        logger << LOG_INFO << F("                  └-- ") << LOGGER_TEXT_GREEN << F("OK") << EndLine;
    }
    else
    {
        logger << LOG_ERROR << F("                  └-- ") << LOGGER_TEXT_RED << F("Not loaded") << EndLine;
    }
}

bool MicroSD_CreateDir(char *name)
{
}

File MicroSD_CreateFile(char *name)
{
    if (strlen(name) >= 13)  // 13 characters is the limit for an filename
    {
        logger << LOG_ERROR << F(" Error on create file (filename too long limit is 13 characters): ") << name << EndLine;
        return File();
    }

    File file = SD.open((const char *)name, FILE_WRITE);
    if (file)
    {
        logger << LOG_INFO << F(" File created: ") << name << EndLine;
    }
    else
    {
        logger << LOG_ERROR << F(" Error on create file: ") << name << EndLine;
    }
    return file;
}

bool MicroSD_WriteToFile(File file, char *data, uint32_t len)
{
    if (file && !file.isDirectory())
    {
        size_t err = file.write(data, len);
        return err != 0;
    }
    else
    {
        return false;
    }
}

bool MicroSD_ReadFromFile(File file, char *buffer, uint32_t len)
{
    if (file && !file.isDirectory())
    {
        size_t err = file.readBytes(buffer, len);
        return err != 0;
    }
    else
    {
        return false;
    }
}

uint32_t MicroSD_CountFiles(char *folderName)
{
    File folder = SD.open(folderName, FILE_READ);
    if (!folder || !folder.isDirectory())
    {
        return 0;
    }
    uint32_t count = 0;
    while (1)  // This loop smells bad becaouse it can generate an infinite loop, or not, something to investigate
    {
        File file = folder.openNextFile();
        if (!file)
        {
            break;
        }
        if (!file.isDirectory())
        {
            count++;
        }
        file.close();
    }
    folder.close();
    return count;
}
