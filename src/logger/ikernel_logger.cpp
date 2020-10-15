#include "ikernel_logger.h"

const __FlashStringHelper *GetStringLogLevel(eLogLevel_t log_lv)
{
    switch (log_lv)
    {
    case LOG_DEBUG:
        return F(LOG_DEBUG_PREFIX_MSG);
    case LOG_INFO:
        return F(LOG_INFO_PREFIX_MSG);
    case LOG_WARN:
        return F(LOG_WARN_PREFIX_MSG);
    case LOG_ERROR:
        return F(LOG_ERROR_PREFIX_MSG);
    default:
        return F("[     ]: ");
    }
}

size_t IKernelLogger::write(const uint8_t *buffer, size_t size)
{
    return this->cout.write(buffer, size);
}

size_t IKernelLogger::write(uint8_t _byte)
{
    return this->cout.write(_byte);
}

IKernelLogger &IKernelLogger::operator<<(LoggerIntBase_e base)
{
    this->intBase = base;
    return *this;
}

IKernelLogger &IKernelLogger::operator<<(LoggerFormatText_e ansiCode)
{
    switch (ansiCode)
    {
    case LOGGER_TEXT_BOLD:
        (*this) << F("\033[1m");
        break;
    case LOGGER_TEXT_YELLOW:
        (*this) << F("\033[93m");
        break;
    case LOGGER_TEXT_RED:
        (*this) << F("\033[91m");
        break;
    case LOGGER_TEXT_GREEN:
        (*this) << F("\033[32m");
        break;
    case LOGGER_TEXT_RESET:
        (*this) << F("\033[0m");
        break;
    }
    return *this;
}

IKernelLogger &IKernelLogger::operator<<(LoggerSpecialChar_t specialChar)
{
    switch (specialChar)
    {
    case EndLine:
        (*this) << LOGGER_TEXT_RESET << F("\n");
        break;
    }
    return *this;
}

IKernelLogger &IKernelLogger::operator<<(eLogLevel_t lvl)
{
    this->canLog = lvl >= this->log_lvl;
    (*this) << LOGGER_TEXT_RESET << GetStringLogLevel(lvl);
    return *this;
}

IKernelLogger &IKernelLogger::operator<<(const __FlashStringHelper *msg)
{
    if (canLog)
        this->cout.print(msg);
    return *this;
}

IKernelLogger &IKernelLogger::operator<<(const String &msg)
{
    if (canLog)
        this->cout.print(msg);
    return *this;
}

IKernelLogger &IKernelLogger::operator<<(const char msg[])
{
    if (canLog)
        this->cout.print(msg);
    return *this;
}

IKernelLogger &IKernelLogger::operator<<(char msg)
{
    if (canLog)
        this->cout.print(msg);
    return *this;
}

IKernelLogger &IKernelLogger::operator<<(unsigned char msg)
{
    if (canLog)
        this->cout.print(msg, (uint8_t)intBase);
    return *this;
}

IKernelLogger &IKernelLogger::operator<<(int msg)
{
    if (canLog)
        this->cout.print(msg);
    return *this;
}

IKernelLogger &IKernelLogger::operator<<(unsigned int msg)
{
    if (canLog)
        this->cout.print(msg);
    return *this;
}

IKernelLogger &IKernelLogger::operator<<(long msg)
{
    if (canLog)
        this->cout.print(msg);
    return *this;
}

IKernelLogger &IKernelLogger::operator<<(unsigned long msg)
{
    if (canLog)
        this->cout.print(msg);
    return *this;
}

IKernelLogger &IKernelLogger::operator<<(double msg)
{
    if (canLog)
        this->cout.print(msg);
    return *this;
}

IKernelLogger &IKernelLogger::operator<<(const Printable &msg)
{
    if (canLog)
        this->cout.print(msg);
    return *this;
}

void IKernelLogger::log(const __FlashStringHelper *msg, eLogLevel_t lvl)
{
    (*this) << lvl << msg << EndLine;
}

void IKernelLogger::log(const String &msg, eLogLevel_t lvl)
{
    (*this) << lvl << msg << EndLine;
}

void IKernelLogger::log(const char msg[], eLogLevel_t lvl)
{
    (*this) << lvl << msg << EndLine;
}

void IKernelLogger::log(char msg, eLogLevel_t lvl)
{
    (*this) << lvl << msg << EndLine;
}

void IKernelLogger::log(unsigned char msg, eLogLevel_t lvl, int base)
{
    (*this) << lvl << msg << EndLine;
}

void IKernelLogger::log(int msg, eLogLevel_t lvl, int base)
{
    (*this) << lvl << msg << EndLine;
}

void IKernelLogger::log(unsigned int msg, eLogLevel_t lvl, int base)
{
    (*this) << lvl << msg << EndLine;
}

void IKernelLogger::log(long msg, eLogLevel_t lvl, int base)
{
    (*this) << lvl << msg << EndLine;
}

void IKernelLogger::log(unsigned long msg, eLogLevel_t lvl, int base)
{
    (*this) << lvl << msg << EndLine;
}

void IKernelLogger::log(double msg, eLogLevel_t lvl, int precision)
{
    (*this) << lvl << msg << EndLine;
}

void IKernelLogger::log(const Printable &msg, eLogLevel_t lvl)
{
    (*this) << lvl << msg << EndLine;
}
