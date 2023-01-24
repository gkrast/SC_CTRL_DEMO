/*
  MCP23S08.c - library for 8-bit IO range extender MCP23S08

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

#include "MCP23S08.h"

// Sets SPI with the hardware pins of ESP8260 and GPIO16 as CS
void MCP23S08Class::begin(SPIClass* SPI)
{
	mySPI = SPI;
	pinMode(CS_IO, OUTPUT);			// CS on  GPIO0 on ESP-12E or D3 on nodeMCU
	digitalWrite(CS_IO, HIGH);		// Set CS to HIGH
	uint8_t buf[] = { 
					 MCP23S08_CONTROL, 
					 MCP23S08_IODIR,
					 0x00, // all outputs
					 0x00,0x00, 0x00, 0x00, 0x00,
					 0x00,0x00, 0x00, 0x00 };
	digitalWrite(CS_IO, LOW);
	mySPI->writeBytes(buf, 12);
	digitalWrite(CS_IO, HIGH);
}

// Releases the SPI to other functions
void MCP23S08Class::end() {
	mySPI->endTransaction();
}

// Set IO mode
void MCP23S08Class::ioMode(uint8_t pin,uint8_t mode) {
	uint8_t iodir;

	// only 8 bits are permitted
	if (mode > 7)
		return;
	digitalWrite(CS_IO, LOW);
	mySPI->transfer(MCP23S08_CONTROL | READ);
	mySPI->transfer(MCP23S08_IODIR);
	iodir = mySPI->transfer(0);
	digitalWrite(CS_IO, HIGH);

	// set the pin and direction
	if (mode == INPUT) {
		iodir |= 1 << pin;
	}
	else {
		iodir &= ~(1 << pin);
	}

	// write the new IODIR
	digitalWrite(CS_IO, LOW);
	mySPI->transfer(MCP23S08_CONTROL | WRITE);
	mySPI->transfer(MCP23S08_IODIR);
	mySPI->transfer(iodir);
	digitalWrite(CS_IO, HIGH);
}

// Set IO pull-up resistor on specified pin
void MCP23S08Class::ioPullUp(uint8_t pin,uint8_t state) {
	uint8_t gppu;

	// only 8 bits!
	if (pin > 7)
		return ;
	
	digitalWrite(CS_IO, LOW);
	mySPI->transfer(MCP23S08_CONTROL | READ);
	mySPI->transfer(MCP23S08_GPPU);
	gppu = mySPI->transfer(0);
	digitalWrite(CS_IO, HIGH);

	// set the pin and direction
	if (state == SET) {
		gppu |= 1 << pin;
	}
	else {
		gppu &= ~(1 << pin);
	}
	
	// write the new GPIO
	digitalWrite(CS_IO, LOW);
	mySPI->transfer(MCP23S08_CONTROL | WRITE);
	mySPI->transfer(MCP23S08_GPPU);
	mySPI->transfer(gppu);
	digitalWrite(CS_IO, HIGH);
}

// Set IO read
uint8_t MCP23S08Class::ioRead(uint8_t pin) {
	uint8_t gpio;
	
	// only 8 bits!
	if (pin > 7)
		return 0;

	digitalWrite(CS_IO, LOW);
	mySPI->transfer(MCP23S08_CONTROL | READ);
	mySPI->transfer(MCP23S08_GPIO);
	gpio = mySPI->transfer(0);
	digitalWrite(CS_IO, HIGH);

	// read the current GPIO
	return (gpio >> pin) & 0x1;
}

// Set IO write
void MCP23S08Class::ioWrite(uint8_t pin, uint8_t state) {
	uint8_t gpio;

	// only 8 bits!
	if (pin > 7)
		return;

	// read the current GPIO output latches
	digitalWrite(CS_IO, LOW);
	mySPI->transfer(MCP23S08_CONTROL | READ);
	mySPI->transfer(MCP23S08_GPIO);
	gpio = mySPI->transfer(0);
	digitalWrite(CS_IO, HIGH);

	// set the pin and direction
	if (state == HIGH) {
		gpio |= 1 << pin;
	}
	else {
		gpio &= ~(1 << pin);
	}

	// write the new GPIO
	digitalWrite(CS_IO, LOW);
	mySPI->transfer(MCP23S08_CONTROL | WRITE);
	mySPI->transfer(MCP23S08_GPIO);
	mySPI->transfer(gpio);
	digitalWrite(CS_IO, HIGH);
}

// read all 8 bits of the io port
uint8_t MCP23S08Class::read() {
	uint8_t gpio;
	
	digitalWrite(CS_IO, LOW);
	mySPI->transfer(MCP23S08_CONTROL | READ);
	mySPI->transfer(MCP23S08_GPIO);
	gpio = mySPI->transfer(0);
	digitalWrite(CS_IO, HIGH);

	// read the current GPIO
	return gpio;
}

//write all 8 bits of the io port
void MCP23S08Class::write(uint8_t gpio) {
	digitalWrite(CS_IO, LOW);
	mySPI->transfer(MCP23S08_CONTROL | WRITE);
	mySPI->transfer(MCP23S08_GPIO);
	mySPI->transfer(gpio);
	digitalWrite(CS_IO, HIGH);
}


MCP23S08Class MCP23S08;

