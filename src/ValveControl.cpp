// ValveControl.cpp
#include "ValveControl.h"
#include "Particle.h"

// Define the pins for valve control
const int pinValveOpen = D0;  // Example pin for opening the valve
const int pinValveClose = D1; // Example pin for closing the valve

// Variable to store calibration data
unsigned long fullOpenTime = 0;

void setupValveControl() {
    pinMode(pinValveOpen, OUTPUT);
    pinMode(pinValveClose, OUTPUT);
}

void openValve() {
    digitalWrite(pinValveOpen, HIGH);
    digitalWrite(pinValveClose, LOW);
    delay(8500 * 15); // Delay for full 8.5mm stroke
    digitalWrite(pinValveOpen, LOW);
}

void closeValve() {
    digitalWrite(pinValveClose, HIGH);
    digitalWrite(pinValveOpen, LOW);
    delay(8500 * 15); // Delay for full 8.5mm stroke
    digitalWrite(pinValveClose, LOW);
}

void manualValveSetting() {
    // Implement manual valve setting logic here
}

void calibrateValve() {
    closeValve();
    unsigned long startTime = millis();
    openValve();
    fullOpenTime = millis() - startTime;
}

void controlValveWithPID(double pidOutput) {
    // Assuming pidOutput is between 0 (fully closed) and 100 (fully open)
    unsigned long targetTime = (fullOpenTime * pidOutput) / 100;
    
    closeValve(); // Start from a known position
    digitalWrite(pinValveOpen, HIGH);
    digitalWrite(pinValveClose, LOW);
    delay(targetTime); // Open the valve for a time proportional to pidOutput
    digitalWrite(pinValveOpen, LOW); // Stop the valve
}
