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
void initializeValvePosition() {
    // Inițializează valva în poziție deschisă
    openValve();
}

void controlValveWithPID(double pidOutput) {
    // Assuming pidOutput is between 0 (fully closed) and 100 (fully open)
    unsigned long targetTime = (fullOpenTime * pidOutput) / 100;

    // Start with the valve in the open position
    openValve(); 

    // If the target position is less open than the current fully open position,
    // close the valve for the necessary time to reach the desired position.
    if (targetTime < fullOpenTime) {
        digitalWrite(pinValveClose, HIGH);
        digitalWrite(pinValveOpen, LOW);
        delay(fullOpenTime - targetTime); // Close the valve to reach the target position
        digitalWrite(pinValveClose, LOW); // Stop the valve
    }
}
