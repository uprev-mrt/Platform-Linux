/**
  *@file linux_spi.c
  *@brief linux SPI module
  *@author Jason Berger
  *@date 04/01/2019
  */

#include "linux_spi.h"


void spi_config(int fd, uint8_t mode, uint8_t bits, int speed)
{
  int ret;

  /*
	 * spi mode
	 */
	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
		pabort("can't set spi mode");

	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1)
		pabort("can't get spi mode");

	/*
	 * bits per word
	 */
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1)
		pabort("can't set bits per word");

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1)
		pabort("can't get bits per word");

	/*
	 * max speed hz
	 */
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		pabort("can't set max speed hz");

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		pabort("can't get max speed hz");

	printf("spi mode: %d\n", mode);
	printf("bits per word: %d\n", bits);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);


}

bool spi_open(int* fd,const char * device, int speed)
{
  *fd = open(device , O_RDWR );
  if(*fd == 1)
  {
    return false;
  }

  /* open with default polarity, 8 bits per word, and speed */
  spi_config(*fd,0,8,speed);
  return true;
}


void spi_close(int fd)
{
  close(fd);
}


int spi_transfer(int fd, uint8_t* tx, uint8_t* rx, int len)
{
  int retVal;
  struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = len,
		.delay_usecs = 0,     //default to device config
		.speed_hz = 0,        //default to device config
		.bits_per_word = 0,   //default to device config
	};

  ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
  if(ret < 1)
    return 0;
  else
    return len;
}
