// ValveControl.cpp

#include "ValveControl.h"
#include "application.h" // Include Particle specific functions

const int pinValveOpen = D6;                             // Valve opening pin
const int pinValveClose = D7;                            // Valve closing pin
unsigned long fullOpenTime = 0;                          // Valve opening time in milliseconds (ms)
const unsigned long maxValveOpenTime = 8500 * 15;        // Total time required for full opening (425 ms)
const unsigned long minValveOpenTime = 8500 * 15 * 0.05; // 5% of the total time required for full opening (425 ms)
unsigned long lastValveActionTime = 0;                   // Time of the last action on the valve (open/close) in milliseconds (ms)

// Valve control pin initialization function
void setupValveControl()
{
    pinMode(pinValveOpen, OUTPUT);  // Set the opening valve pin as output
    pinMode(pinValveClose, OUTPUT); // Set the closing valve pin as output
}

// Valve opening function
void openValve()
{
    if (millis() - lastValveActionTime >= 15000) // 15 seconds delay between valve actions
    {
        digitalWrite(pinValveOpen, HIGH);   // Open the valve
        digitalWrite(pinValveClose, LOW);   // Stop the valve
        Serial.println("Opening valve..."); // Print to the serial monitor
        lastValveActionTime = millis();     // Update the last valve action time
        fullOpenTime += 15000;              // Update the valve opening time with 15 seconds
    }
}

// Valve closing function
void closeValve()
{
    if (millis() - lastValveActionTime >= 15000 && fullOpenTime > minValveOpenTime) // 15 seconds delay between valve actions and the valve is open more than 5%
    {
        digitalWrite(pinValveClose, HIGH);  // Close the valve
        digitalWrite(pinValveOpen, LOW);    // Stop the valve
        Serial.println("Closing valve..."); // Print to the serial monitor
        lastValveActionTime = millis();     // Update the last valve action time
        fullOpenTime -= 15000;              // Update the closing time
    }
}

// Valve stop function
void stopValve()
{
    digitalWrite(pinValveOpen, LOW);  // Stop the valve
    digitalWrite(pinValveClose, LOW); // Stop the valve
    Serial.println("Stop valve...");  // Print to the serial monitor
}

// Valve calibration function
void calibrateValveOnStartup()
{

    openValve();             // Open the valve to 100% opening at startup
    delay(maxValveOpenTime); // Delay for full opening
    stopValve();             // Stop the valve

    closeValve();                               // Close the valve to 5% opening at startup (anti freeze)
    delay(maxValveOpenTime - minValveOpenTime); // Delay for full closing minus 5% opening time (anti freeze)
    stopValve();                                // Stop the valve

    fullOpenTime = minValveOpenTime; // Set the valve to 5% opening at startup (anti freeze)
}

// Valve control anti freeze function ensuring that the valve is open at least 5%
void ensureAntiFreeze()
{
    if (fullOpenTime < minValveOpenTime) // If the valve is open less than 5%
    {
        openValve(); // Open the valve to 5%½ to prevent freezing of the water in the radiator and pipes in the winter season (anti freeze)
    }
}