//https://www.digikey.com/en/maker/blogs/2019/how-to-use-gpio-on-the-raspberry-pi-with-c

#include <iostream>		// Include all needed libraries here
#include <wiringPi.h>

using namespace std;		// No need to keep using “std”

int main()
{
<<<<<<< HEAD
wiringPiSetup();			// Setup the library
pinMode(8, OUTPUT);		// Configure GPIO0 as an output
pinMode(9, INPUT);		// Configure GPIO1 as an input

// Main program loop
while(true)
{
	// Button is pressed if digitalRead returns 0
	if(digitalRead(9) == true)
{	
	// Toggle the LED
	digitalWrite(8, !digitalRead(8));
delay(500); 	// Delay 500ms
}
}
=======
	wiringPiSetup();			// Setup the library
	pinMode(2, OUTPUT);		// Configure GPIO0 as an output
	pinMode(3, INPUT);		// Configure GPIO1 as an input

	// Main program loop
	while(true)
	{
		// Button is pressed if digitalRead returns 0
		if(digitalRead(1) == 1)
		{	
			// Toggle the LED
			digitalWrite(0, !digitalRead(0));
			delay(500); 	// Delay 500ms
		}
	}
>>>>>>> 516ed7c85586877f9238776e230202cdd2e229f8
	return 0;
}
