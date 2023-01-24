/*
  MCP3004.c - library for 4 channels 10-bit ADC MCP3004

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

#include "MCP3004.h"


// Sets SPI with GPIO0 as CS
void MCP3004Class::begin(SPIClass* SPI)
{
	mySPI = SPI;
	pinMode(CS_ADC, OUTPUT);		// CS on  GPIO16 on ESP-12E or D0 on nodeMCU
	digitalWrite(CS_ADC, HIGH);		// Set CS to HIGH
}

// Reda ADC from selected channel (0 to 3) single-ended
float MCP3004Class::readADC(uint8 chan) {
	uint16_t adc;
	digitalWrite(CS_ADC, LOW);
	mySPI->transfer(START);
	adc = mySPI->transfer(SINGLE+(chan<<4));
	adc = (adc << 8);
	adc += mySPI->transfer(0);
	digitalWrite(CS_ADC, HIGH);
	adc = adc & 0b1111111111;
	return adc * LSB;
}

MCP3004Class MCP3004;

