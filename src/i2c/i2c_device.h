/**
 * @file i2c_device.hpp
 * @author Daniel Polanco (jpolanco@getinsoft.com)
 * @brief I2CDevice class definition
 * @version 1.0
 * @date 2020-01-07
 *
 */
#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

#include <Arduino.h>
#include <Wire.h>

/**
 * @brief I2CDevice class for I2CBus
 * @details Defines an base class overridable, is only an
 *          interface to allocate inside the I2CBus
 */
class I2CDevice
{
private:
  /**
   * @brief [Private Attribute] I2C Address of the device
   *
   */
  uint8_t device_addrs;

  virtual void _writeCommand(uint8_t cmd, bool begin = true, bool end = true)
  {
    if (begin)
      port->beginTransmission(device_addrs);
    port->write(cmd);
    if (end)
      port->endTransmission();
  }

protected:
  /**
   * @brief [Protected Attribute] I2C Port where is connected
   *
   */
  TwoWire* port;

  void _setReg(uint8_t reg, bool end = false)
  {
    port->beginTransmission(address());
    port->write(reg);
    if (end) {
      port->endTransmission();
    }
  }

  template<typename T>
  void _writeReg(uint8_t reg, T _data)
  {
    _setReg(reg);
    port->write(sizeof(T));
    port->write(_data);
    port->endTransmission();
  }

  template<typename T>
  T _readReg(uint8_t reg)
  {
    T _data = T();
    _setReg(reg, true);
    uint8_t bytes = port->requestFrom(address(), sizeof(T));
    if (bytes == sizeof(T)) {
      port->readBytes((uint8_t*)&_data, sizeof(T));
    }
    return _data;
  }

  uint8_t requestBytes(uint8_t* buffer, uint8_t length) {
    if (!buffer) { return 0; }
    uint8_t bytes = port->requestFrom(address(), length);
    uint8_t index_buffer = 0U;
    while (port->available()) {
      if (index_buffer >= length) {
        break;
      }
      buffer[index_buffer] = port->read();
      index_buffer ++;
      if (buffer[index_buffer] == 0) {
        break;
      }
    }
    return bytes;
  }

  uint8_t requestBytes(char* buffer, uint8_t length) {
    return requestBytes((uint8_t*)buffer, length);
  }

public:
  /**
   * @brief [Setter] Set the Port
   *
   * @param wire I2C Port
   */
  virtual void setPort(TwoWire& wire) { port = &wire; }

  /**
   * @brief [Public Method] Begins the device at the address
   *
   * @param addr Address where is the device
   * @return bool If the port is not NULL
   */
  virtual bool begin(uint8_t addr)
  {
    this->setAddress(addr);
    if (port == NULL) {
      return false;
    }
    port->begin();
    return isConnected();
  }

  /**
   * @brief [Public Method] Checks if the device is connected
   *        to the bus
   *
   * @return bool If the device is connected
   */
  virtual bool isConnected()
  {
    uint8_t error;
    if (port == NULL) {
      return false;
    }
    port->beginTransmission(this->address());
    error = port->endTransmission();
    return error == 0;
  }

  /**
   * @brief [Getter] Gets the device address
   *
   * @return uint8_t
   */
  virtual uint8_t address() const { return device_addrs; }

  /**
   * @brief [Setter] Set the device address
   *
   * @param addr I2C Address
   */
  virtual void setAddress(uint8_t addr) { device_addrs = addr; }

  virtual void writeCommand(uint8_t cmd) { _writeCommand(cmd); }

  virtual bool readCommand(uint8_t* buffer, uint8_t expected_bytes)
  {
    uint8_t bytes_readed = port->requestFrom(address(), expected_bytes);
    if (bytes_readed != expected_bytes) {
      port->setTimeout(1000);
      port->readBytes(buffer, expected_bytes);
    }
    return bytes_readed == expected_bytes;
  }

  virtual void writeReg(uint8_t reg, uint8_t _data)
  {
    _writeReg<uint8_t>(reg, _data);
  }

  virtual void writeReg(uint8_t reg, uint16_t _data)
  {
    _writeReg<uint16_t>(reg, _data);
  }

  virtual void writeReg(uint8_t reg, uint32_t _data)
  {
    _writeReg<uint32_t>(reg, _data);
  }

  virtual uint8_t readReg8bits(uint8_t reg) { return _readReg<uint8_t>(reg); }

  virtual uint16_t readReg16bits(uint8_t reg)
  {
    return _readReg<uint16_t>(reg);
  }

  virtual uint32_t readReg32bits(uint8_t reg)
  {
    return _readReg<uint32_t>(reg);
  }
};

#endif // !I2C_DEVICE_H