/* The Public License
 ******************************************************************************
 *                                                                            *
 * Copyright (c) 2023 by Senzotic											  *
 *                                                                            *
 ******************************************************************************
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.

	This code demonstrates the functionality of the EBS-G board
	----------------------------------------------------------------------------------------------------------
	Application description:
	----------------------------------------------------------------------------------------------------------
	Each of the 8 IO pins of the IO extender (MCP23S08) drives one LED with 3.3V
	The LEDs powered by the IO extender ports 0 t0 5 are lit one at time and in each direction (left then right) with adjustable speed 
	One POT between 3.3V and GND with its center tap connected to channel 3 of the ADC (MCP3004) is used to adjust the speed of the running LEDs
	The POT's center tap voltage can be varied from 0 to 3.3V which controls the speed of the LEDs from the maximum and the minimum level
	The LCD displays up or down counter for each change in the direction of the LEDs.
	Pushing one button clears the counter or loads it with max value. Pushing the second button toggles the counting direction.
	Debouncing of the two buttons can be improved.
*/

// LCD driver libraries
#include <SSD1306Wire.h>
#include <OLEDDisplayUi.h>
#include <OLEDDisplayFonts.h>
#include <OLEDDisplay.h>

// Driver for serial interfaces
#include <SPI.h>				// SPI functions
#include <Wire.h>				// IIC functions and more

#include "app.h"


//Local variables
uint8_t ioPins = 1;
uint8_t dir = 1;
uint8_t wait = 10;
uint8_t inc = 1;
SPISettings mySettings;
float ADC;
String LCD_Buffer[MAX_BUFF];

/////////////////////////////////////////////////////////////////////
//                  APPLICATION INITIALIZATION                     //
/////////////////////////////////////////////////////////////////////
void setup()
{
	// Open serial port connection
	Serial.begin(9600);
	cout << "Initilizing..." << endl << endl;

	LCD.Init();
	LCD.setTitle("Initializing...");
	LCD.setHoldTime(50);

	// Setup the SPI shared by IO and ADC
	SPI.begin();
	mySettings._clock = 50000;
	mySettings._bitOrder = MSBFIRST;
	mySettings._dataMode = SPI_MODE0;
	SPI.beginTransaction(mySettings);

	// Setup IO chip
	MCP23S08.begin(&SPI);
	for (int k = 0; k < 8; k++) {
		MCP23S08.ioMode(k, OUTPUT);
		MCP23S08.ioPullUp(k, RESET);
	}
	MCP23S08.write(0xFF);
	// Button input pins
	MCP23S08.ioMode(6, INPUT);
	MCP23S08.ioMode(7, INPUT);
	MCP23S08.ioPullUp(6, SET);
	MCP23S08.ioPullUp(7, SET);
	
	// Setup the ADC chip
	MCP3004.begin(&SPI);

	cout << "Running..." << endl << endl;

}

void loop()
{
	
	static int ctr = 0;
	static bool ct_down = 0;
	ADC = MCP3004.readADC(0);
	cout << "ADC: " << ADC << endl;
	wait = (uint8_t)(100 * (ADC / 3.3));
	if (wait == 0) wait = 50;
		
	MCP23S08.write(ioPins);
	if (dir) {
		ioPins = ioPins << 1;
		if (ioPins == 0b01000000) {
			ioPins = 0b00100000;
			dir = 0;
			if (ct_down) {
				ctr--;
			}
			else {
				ctr++;
			}
			LCD_Buffer[0] = String(ctr);
			LCD.loadBuffer(LCD_Buffer);
			if (ct_down) {
				LCD.showData("Count down");
			}
			else {
				LCD.showData("Count up");
			}
		}
	}
	else {
		ioPins = ioPins >> 1;
		if (ioPins == 0) {
			ioPins = 1;
			dir = 1;
			if (ct_down) {
				ctr--;
			}else{
				ctr++;
			}
			LCD_Buffer[0] = String(ctr);
			LCD.loadBuffer(LCD_Buffer);
			if (ct_down) {
				LCD.showData("Count down");
			}
			else {
				LCD.showData("Count up");
			}
			
		}		
	}
	delay(wait);
	
	if (MCP23S08.ioRead(7) == 0) {
		delay(100);
		if (MCP23S08.ioRead(7) == 0) {
			ct_down = !ct_down;
			ctr = ct_down ? 0xFFFF : 0;
		}
	}
	if (MCP23S08.ioRead(6) == 0) {
		delay(100);
		if (MCP23S08.ioRead(6) == 0) {
			ctr = ct_down ? 0xFFFF : 0;
		}
	}
}
