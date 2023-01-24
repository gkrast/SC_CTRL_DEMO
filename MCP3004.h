/*
  MCP3004.h - library for 4 channels 10-bit ADC MCP3004

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

#ifndef _MCP3004_h
#define _MCP3004_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SPI.h>

/// <summary>
/// Class for interfacing with MCP23S08 IO range extender
/// see datasheet here: https://ww1.microchip.com/downloads/en/DeviceDoc/21295d.pdf
/// </summary>
class MCP3004Class
{
 protected:
	 SPIClass* mySPI;

 public:
	void begin(SPIClass* SPI);
	float readADC(uint8 chan);
};

// CS is software controlled on PIN 16 of ESP8260 or D0 of the nodeMCU
#define CS_ADC	16

// Reference voltage VREF
#define VREF	3.3
#define LSB		VREF/1024

#define START	0b00000001 
#define SINGLE	0b10000000

extern MCP3004Class MCP3004;

#endif

