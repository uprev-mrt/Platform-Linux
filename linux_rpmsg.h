/**
  *@file linux_rpmsg.h
  *@brief header for RPMsg interface
  *@author Jason Berger
  *@date 8/28/2019
  */
#pragma once

#include <stdio.h>
#include <stdlib.h>

using namespace std;

class RPMsg
{
  RPMsg();
public:
  void open(const char* dev);
  void close();
  void read(uint8_t* data, int len);
  void write(uint8_t* data, int len);
private:
  int fd;
};
