#pragma once
#ifndef _APP_h
#define _APP_h

#define MAX_BUFF 6			   // size of LCD  buffer

// Enumerator for font size on the LCD
enum font_sizes {
	SMALL,
	MEDIUM,
	LARGE
};

// C++ libraries
#include <iostream>
#include <string>
#include <stdbool.h>
using namespace std;		// standard c++ library for cout <<


#include <Arduino.h>		// Arduino core library
#include <Wire.h>           // I2C function
#include <SSD1306Wire.h>    // SSD1306 LCD library

#include "myLCD.h"				// LCD operations
#include "fonts.h"				// Bits of fonts
#include "MCP23S08.h"
#include "MCP3004.h"

#endif