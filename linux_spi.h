/**
  *@file linux_spi.h
  *@brief linux SPI module
  *@author Jason Berger
  *@date 04/01/2019
  */

  #include <linux/types.h>
  #include <linux/spi/spidev.h>

  /**
    *@brief open spi port
    *@param fd ptr to int to store spi handle
    *@param device name of device to connect to i.e. "/dev/ttyS16"
    *@param baudrate baudrate for connection [2400 ,4800, 9600, 19200, 38400, 57600, 115200]
    *@return true if successful
    *@return false if there was a problem
    */
  bool spi_open(int* fd,const char * device, int maxSpeed);

  /**
    *@brief closes the spi port
    *@param fd spi handle
    */
  void spi_close(int fd);

  /**
    *@brief spi spi_transfer
    *@param fd spi handle
    *@param tx ptr to data to send ( null for rx only)
    *@param rx ptr to store data read ( null for tx only)
    *@param number of bytes to read
    *@return number of bytes read
    */
  int spi_transfer(int fd, uint8_t* tx, uint8_t* rx, int len);
