Application description:
--
The LEDs powered by the IO extender (MCP23S08) ports 0 t0 5 are lit one at time and in each direction (left then right) with adjustable speed
One POT between 3.3V and GND with its center tap connected to channel 3 of the ADC (MCP3004) is used to adjust the speed of the running LEDs
The POT's center tap voltage can be varied from 0 to 3.3V which controls the speed of the LEDs from the maximum and the minimum level
The LCD displays up or down counter for each change in the direction of the LEDs.
Pushing one button clears the counter or loads it with max value. Pushing the second button toggles the counting direction.
This code is provided with the hope to be usefull as a startup application with NodeMCU and EBS-G development board
Happy coding!
