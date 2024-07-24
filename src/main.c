#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#include <fcntl.h>
#include <linux/i2c.h>

#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

static const char *i2c_device = "/dev/i2c-1";
static const char address = 0x3f;

unsigned char i2c_tx_buf[2];
unsigned char i2c_rx_buf[2];

int main()
{

  int i2c;
  struct i2c_msg msgs[2];
  struct i2c_rdwr_ioctl_data msgset[1];

  i2c = open(i2c_device, O_RDWR);
  if (i2c <0) {
    perror("Can't open I2C device:");
    exit(0);
  }

  // set first element of the buffer to the register address
  i2c_tx_buf[0] = 0x01;

  // configure i2c message format
  msgs[0].addr = address;
  msgs[0].flags = 0;
  msgs[0].len = 1;
  msgs[0].buf = i2c_tx_buf;

  msgs[1].addr = address;
  msgs[1].flags = I2C_M_RD;
  msgs[1].len = 1;
  msgs[1].buf = i2c_rx_buf;

  // pass the messages to IOCTL RDWR structure
  msgset[0].msgs = msgs;
  msgset[0].nmsgs = 2;

  // execute transaction
  if (ioctl(i2c, I2C_RDWR, &msgset) < 0) {
    perror("ioctl(I2C_RDWR) in i2c_read");
  }

  if (i2c_rx_buf[0] == 0xa0)
    printf("STTS22H Detected\n");
}
