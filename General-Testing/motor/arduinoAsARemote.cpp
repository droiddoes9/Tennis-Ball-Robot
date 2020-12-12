#include <iostream>
#include "motor.h"
#include <wiringPi.h>

using namespace std;

#define LEFTPIN 5
#define RIGHTPIN 6



double Lpower = 0;
double Rpower = 0;

volatile int timeInit = 0;
volatile int baseTime = 0;
volatile int count = 0;

double superMap(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void rwmReaderLRise(){
    
    baseTime = micros();

    //Lpower = superMap(timeGap, 15, 2036, -1, 1);
    //baseTime = micros();
    //delay(2);
    //count++;
}
void rwmReaderLFall(){
    //printf("\nTHE TIME: %.2f", micros());
    unsigned int timeGap = micros()-baseTime;
    
    //printf("\nLEFT: %.2f", Lpower);
    Lpower = timeGap;
    cout << "\r" << Lpower;
    //Lpower = superMap(timeGap, 15, 2041, -1, 1);
    //baseTime = micros();
    baseTime = micros();
}

void counter(){
    count++;
}

int main()
{
    wiringPiSetup();
    pinMode(LEFTPIN, INPUT);
    pinMode(RIGHTPIN, INPUT);

    
    //wiringPiISR (LEFTPIN, INT_EDGE_RISING, &rwmReaderLRise);
    wiringPiISR (LEFTPIN, INT_EDGE_FALLING, &counter);
    //while (true){
        //timeInit = micros(); //gets a time baseline
        //baseTime = micros();
        
        delay(2000);
        cout << count << "\n";
        //delay(2);
        //wiringPiISR (LEFTPIN, INT_EDGE_FALLING, &rwmReaderLFall);
        
        //printf("\nLEFT: %.2f", Lpower);
        //while(digitalRead(LEFTPIN) == 1){}
        //printf("\nTIME:", timeInit);
    //}
}

