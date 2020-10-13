#ifndef KERNEL_OSSTREAM_H
#define KERNEL_OSSTREAM_H

#include <Print.h>

class osstream
{
private:
  Print &cout;

public:
  osstream(Print &out) : cout(out) {}
  virtual osstream &operator<<(const __FlashStringHelper *msg)
  {
    cout.print(msg);
    return *this;
  }
  virtual osstream &operator<<(const String &msg)
  {
    cout.print(msg);
    return *this;
  }
  virtual osstream &operator<<(const char msg[])
  {
    cout.print(msg);
    return *this;
  }
  virtual osstream &operator<<(char msg)
  {
    cout.print(msg);
    return *this;
  }
  virtual osstream &operator<<(unsigned char msg)
  {
    cout.print(msg);
    return *this;
  }
  virtual osstream &operator<<(int msg)
  {
    cout.print(msg);
    return *this;
  }
  virtual osstream &operator<<(unsigned int msg)
  {
    cout.print(msg);
    return *this;
  }
  virtual osstream &operator<<(long msg)
  {
    cout.print(msg);
    return *this;
  }
  virtual osstream &operator<<(unsigned long msg)
  {
    cout.print(msg);
    return *this;
  }
  virtual osstream &operator<<(double msg)
  {
    cout.print(msg);
    return *this;
  }
  virtual osstream &operator<<(const Printable &msg)
  {
    cout.print(msg);
    return *this;
  }
};

#endif // !KERNEL_OSSTREAM_H