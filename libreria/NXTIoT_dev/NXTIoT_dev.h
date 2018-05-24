/*
NXTIoT_dev.h  - Libreria para la comunicación por Sigfox con el Devkit de NXTIoT
  Por Gabino Perez - WND Mexico
  24 de mayo 2018
  Para uso publico.
*/
#ifndef NXTIoT_dev_h
#define NXTIoT_dev_h

#include "Arduino.h"

#define enable_module 7

class NXTIoT_dev
{
	public: 
	NXTIoT_dev();
	void initpayload();
	void sendmessage();
	void addint(int var2);
	void addfloat(float var1);
	String bufer; //variable donde guardaremos nuestro payload
};

#endif