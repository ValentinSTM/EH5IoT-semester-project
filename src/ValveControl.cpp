// ValveControl.cpp
#include "ValveControl.h"
#include "Particle.h"

// Define the pins for valve control
const int pinValveOpen = D0;  // Example pin for opening the valve
const int pinValveClose = D1; // Example pin for closing the valve

void setupValveControl()
{
    pinMode(pinValveOpen, OUTPUT);
    pinMode(pinValveClose, OUTPUT);
}

void openValve()
{
    digitalWrite(pinValveOpen, HIGH);
    digitalWrite(pinValveClose, LOW);
    delay(8500 * 15); // Delay for full 8.5mm stroke
    digitalWrite(pinValveOpen, LOW);
}

void closeValve()
{
    digitalWrite(pinValveClose, HIGH);
    digitalWrite(pinValveOpen, LOW);
    delay(8500 * 15); // Delay for full 8.5mm stroke
    digitalWrite(pinValveClose, LOW);
}

void manualValveSetting()
{
    // Implement manual valve setting logic here
}
