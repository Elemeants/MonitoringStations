#if !defined(KERNEL_ILOGGER_H)
#define KERNEL_ILOGGER_H

#include <Print.h>

#include "config.h"
#include "utils/datetime.h"

// Local macro for prefix debug msg
#define LOG_DEBUG_PREFIX_MSG "[\033[1m\033[35mDEBUG\033[0m]: "
// Local macro for prefix info msg
#define LOG_INFO_PREFIX_MSG "[\033[1m\033[32mINFO \033[0m]: "
// Local macro for prefix warn msg
#define LOG_WARN_PREFIX_MSG "[\033[1m\033[93mWARN \033[0m]: "
// Local macro for prefix error msg
#define LOG_ERROR_PREFIX_MSG "[\033[1m\033[91mERROR\033[0m]: "

typedef enum
{
    // Log at debug level
    LOG_DEBUG,
    // Log at info level
    LOG_INFO,
    // Log at warning level
    LOG_WARN,
    // Log at error level
    LOG_ERROR,
    // Log at any level
    LOG_MASTER
} eLogLevel_t;

typedef enum
{
    EndLine
} LoggerSpecialChar_t;

typedef enum
{
    LOGGER_TEXT_BOLD,
    LOGGER_TEXT_YELLOW,
    LOGGER_TEXT_RED,
    LOGGER_TEXT_GREEN,
    LOGGER_TEXT_RESET
} LoggerFormatText_e;

typedef enum
{
    INT_BIN = 2,
    INT_OCT = 8,
    INT_DEC = 10,
    INT_HEX = 16
} LoggerIntBase_e;

const __FlashStringHelper *GetStringLogLevel(eLogLevel_t);

class IKernelLogger : public Print
{
    eLogLevel_t log_lvl;

    Print &cout;

    bool canLog = false;
    bool printTime = false;
    LoggerIntBase_e intBase;

public:
    IKernelLogger(Print &printOut)
        : cout(printOut), intBase(INT_DEC)
    {
    }

    virtual void begin() = 0;
    virtual void begin(uint32_t) = 0;
    virtual void end() = 0;
    virtual void flush();

    virtual size_t write(const uint8_t *buffer, size_t size);
    virtual size_t write(uint8_t _byte);

    void setLogTime(Time_s);

    eLogLevel_t logLevel() const { return this->log_lvl; }
    void setLogLevel(const eLogLevel_t &_lvl) { this->log_lvl = _lvl; }

    virtual IKernelLogger &operator<<(LoggerIntBase_e);
    virtual IKernelLogger &operator<<(LoggerFormatText_e);
    virtual IKernelLogger &operator<<(LoggerSpecialChar_t);
    virtual IKernelLogger &operator<<(eLogLevel_t);
    virtual IKernelLogger &operator<<(const __FlashStringHelper *);
    virtual IKernelLogger &operator<<(const String &);
    virtual IKernelLogger &operator<<(const char[]);
    virtual IKernelLogger &operator<<(char);
    virtual IKernelLogger &operator<<(unsigned char);
    virtual IKernelLogger &operator<<(int);
    virtual IKernelLogger &operator<<(unsigned int);
    virtual IKernelLogger &operator<<(long);
    virtual IKernelLogger &operator<<(unsigned long);
    virtual IKernelLogger &operator<<(double);
    virtual IKernelLogger &operator<<(const Printable &);

    virtual void log(const __FlashStringHelper *, eLogLevel_t);
    virtual void log(const String &, eLogLevel_t);
    virtual void log(const char[], eLogLevel_t);
    virtual void log(char, eLogLevel_t);
    virtual void log(unsigned char, eLogLevel_t, int = DEC);
    virtual void log(int, eLogLevel_t, int = DEC);
    virtual void log(unsigned int, eLogLevel_t, int = DEC);
    virtual void log(long, eLogLevel_t, int = DEC);
    virtual void log(unsigned long, eLogLevel_t, int = DEC);
    virtual void log(double, eLogLevel_t, int = 2);
    virtual void log(const Printable &, eLogLevel_t);
};

extern IKernelLogger &logger;

#endif  // KERNEL_ILOGGER_H
