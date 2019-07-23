/**
  *@file atmel_start_abstract.h
  *@brief Abstraction header for Atmel MCUs using the Atmel Start framework
  *@author Jason Berger
  *@date 2/18/2019
  */

#pragma once

#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "linux_spi.h"
#include "linux_uart.h"



//Delay Abstraction
#define MRT_DELAY_MS(ms) sleep(ms/1000)

//Uart Abstraction
typedef int mrt_uart_handle_t;
#define MRT_UART_TX(handle, data, len, timeout) uart_write(handle, data, len)
#define MRT_UART_RX(handle, data, len, timeout) uart_read(handle, data, len)

//GPIO Abstraction
//typedef uint8_t mrt_gpio_t;
//typedef enum gpio_port mrt_gpio_port_t;
//#define MRT_GPIO_WRITE(pin,val)
//#define MRT_GPIO_READ(pin)
//#define MRT_GPIO_PORT_WRITE(port, mask, val)
//#define MRT_GPIO_PORT_READ(port)

//I2C Abstraction
//typedef io_descriptor* mrt_i2c_handle_t;
//typedef int32_t mrt_i2c_status_t;
//#define MRT_I2C_MASTER_TRANSMIT(handle ,addr,data,len, stop, timeout)
//#define MRT_I2C_MASTER_RECEIVE(handle ,addr, data, len, stop, timeout)
//#define MRT_I2C_MEM_WRITE(handle, addr, mem_addr, mem_size, data, len, timeout ) i2c_m_sync_cmd_write(handle, mem_addr, data, len)
//#define MRT_I2C_MEM_READ(handle, addr, mem_addr, mem_size, data, len, timeout ) i2c_m_sync_cmd_read(handle, mem_addr, data, len)


//SPI Abstraction
typedef int mrt_spi_handle_t;
typedef int32_t mrt_spi_status_t;
#define MRT_SPI_TRANSFER(handle ,tx, rx ,len, timeout)  spi_transfer(handle, tx, rx, len)
#define MRT_SPI_TRANSMIT(handle, tx, len, timeout) spi_transfer(handle, tx, NULL, len)
#define MRT_SPI_RECIEVE(handle, tx, len, timeout) spi_transfer(handle, NULL, rx, len)


//printf
#define MRT_PRINTF(f_, ...) printf((f_), __VA_ARGS__)
