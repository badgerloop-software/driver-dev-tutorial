#ifndef __i2c_h__
#define __i2c_h__

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

class I2c {
 private:
  int fd;
  int bus;
  int deviceAddress;
  int openMode;
  int write_byte(uint8_t reg);

 protected:
  I2c(int bus, int addr);
  ~I2c();
  int open_i2c();
  bool is_open();
  int read_data(uint8_t *buff, int size);
  int read_bytes_from_reg(uint8_t reg, uint8_t *buff, int nBytes);

  // Returns the value of a register given its address
  uint8_t read_from_reg(uint8_t reg);

  
  // Writes data of any size to a register given its address and the data
  // Returns 0 on success
  template <class T>
  int write_data(uint8_t reg, T val);
};

template <class T>
int I2c::write_data(uint8_t reg, T val) {
  uint8_t size = sizeof(T) + 1;
  uint8_t buff[size];
  buff[0] = reg;
  std::memcpy(&buff[1], &val, sizeof(T));
  if (write(this->fd, buff, size) != size) {
    std::cerr << "I2C write data error\n";
    return -EIO;
  }
#ifdef TEST
  usleep(500000);
#endif
  return 0;
}

#endif
