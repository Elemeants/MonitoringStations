#if !defined(KERNEL_ILOGGER_H)
#define KERNEL_ILOGGER_H

#include "config.h"
#include <HardwareSerial.h>
#include <Logger.h>

#include "utils/osstream.h"

typedef enum
{
    EndLine
} SpecialChar_t;

class IKernelLogger : public ILogger
{
    eLogLevel_t log_lvl;
    Print &cout;
    Print *secondary_cout;
    bool canLog = false;

public:
    IKernelLogger(Print &printOut)
        : cout(printOut), secondary_cout(NULL)
    {
    }
    
    void setSecondaryOutput(Print *printeable) {
        secondary_cout = printeable;
    }
    
    // [Public Method] Begins serial communication
    virtual void begin() = 0;
    // [Public Method] Begins serial communication
    virtual void begin(uint32_t) = 0;
    // [Public Method] Ends serial communication
    virtual void end() = 0;
    // [Public Method] Flush implementation
    virtual void flush() {
        // cout.flush();
        // if (secondary_cout) { secondary_cout->flush(); }
    }
    // [Override Method] Implements buffer writing into port
    virtual size_t write(const uint8_t *buffer, size_t size) {
        if (secondary_cout) { secondary_cout->write(buffer, size); }
        return cout.write(buffer, size);
    }
    // [Override Method] Implements data writting into port
    virtual size_t write(uint8_t _byte) {
        if (secondary_cout) { secondary_cout->write(_byte); }
        return cout.write(_byte);
    }
    // [Public Getter] Gets the log level
    eLogLevel_t logLevel() const override
    {
        return log_lvl;
    }
    // [Public Setter] Sets the log level
    void setLogLevel(const eLogLevel_t &_lvl) override
    {
        log_lvl = _lvl;
    }

    virtual IKernelLogger &operator<<(eLogLevel_t logLevel)
    {
        canLog = logLevel >= log_lvl;
        if (canLog)
            printPrefix();
        *this << GetStringLogLevel(logLevel);
        return *this;
    }
    virtual IKernelLogger &operator<<(SpecialChar_t endl)
    {
        if (canLog)
        {
            cout.println();
            flush();
        }
        return *this;
    }
    virtual IKernelLogger &operator<<(const __FlashStringHelper *msg)
    {
        if (canLog)
            cout.print(msg);
        return *this;
    }
    virtual IKernelLogger &operator<<(const String &msg)
    {
        if (canLog)
            cout.print(msg);
        return *this;
    }
    virtual IKernelLogger &operator<<(const char msg[])
    {
        if (canLog)
            cout.print(msg);
        return *this;
    }
    virtual IKernelLogger &operator<<(char msg)
    {
        if (canLog)
            cout.print(msg);
        return *this;
    }
    virtual IKernelLogger &operator<<(unsigned char msg)
    {
        if (canLog)
            cout.print(msg);
        return *this;
    }
    virtual IKernelLogger &operator<<(int msg)
    {
        if (canLog)
            cout.print(msg);
        return *this;
    }
    virtual IKernelLogger &operator<<(unsigned int msg)
    {
        if (canLog)
            cout.print(msg);
        return *this;
    }
    virtual IKernelLogger &operator<<(long msg)
    {
        if (canLog)
            cout.print(msg);
        return *this;
    }
    virtual IKernelLogger &operator<<(unsigned long msg)
    {
        if (canLog)
            cout.print(msg);
        return *this;
    }
    virtual IKernelLogger &operator<<(double msg)
    {
        if (canLog)
            cout.print(msg);
        return *this;
    }
    virtual IKernelLogger &operator<<(const Printable &msg)
    {
        if (canLog)
            cout.print(msg);
        return *this;
    }
};

extern IKernelLogger &logger;

#endif // KERNEL_ILOGGER_H
