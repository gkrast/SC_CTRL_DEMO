/*
  MCP23S08.h - library for 8-bit IO range extender MCP23S08

  Copyright (c) 2022 George Krastev. All rights reserved.
  This file is for esp8266 in Arduino environment.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

*/

#ifndef _MCP23S08_h
#define _MCP23S08_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SPI.h>

/// <summary>
/// Class for interfacing with MCP23S08 IO range extender
/// see datasheet here: https://ww1.microchip.com/downloads/en/DeviceDoc/MCP23008-MCP23S08-Data-Sheet-20001919F.pdf
/// </summary>
class MCP23S08Class
{
 protected:
	 SPIClass* mySPI;

 public:
	void begin(SPIClass* SPI);
	void end();
	void ioMode(uint8_t pin, uint8_t mode);
	void ioPullUp(uint8_t pin, uint8_t state);
	uint8_t ioRead(uint8_t pin);
	void ioWrite(uint8_t pin, uint8_t state);
	uint8_t read();
	void write(uint8_t gpio);
};

// CS is software controlled on PIN 0 of ESP8260 or D3 of the nodeMCU
#define CS_IO	0

//MCP23S08 bus address and R/W control
#define MCP23S08_CONTROL 0b01000100 

// Read and write masks
#define READ	1
#define WRITE	0
#define SET		1
#define RESET	0

// MCP23008 registers
#define MCP23S08_IODIR 0x00		//I/O direction register
#define MCP23S08_IPOL 0x01		//Input polarity register
#define MCP23S08_GPINTEN 0x02	//Interrupt-on-change control register
#define MCP23S08_DEFVAL  0x03	//Default compare register for interrupt-on-change
#define MCP23S08_INTCON 0x04	//Interrupt control register
#define MCP23S08_IOCON 0x05		//Configuration register
#define MCP23S08_GPPU 0x06		//Pull-up resistor configuration register
#define MCP23S08_INTF 0x07		//Interrupt flag register
#define MCP23S08_INTCAP 0x08	//Interrupt capture register
#define MCP23S08_GPIO 0x09		//Port register
#define MCP23S08_OLAT 0x0A		//Output latch register

extern MCP23S08Class MCP23S08;


#endif

