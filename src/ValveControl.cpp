// ValveControl.cpp

#include "ValveControl.h"
#include "application.h" // Include Particle specific functions
#include "Common.h"

const int PIN_VALVE_OPEN = D6;  // Valve opening pin
const int PIN_VALVE_CLOSE = D7; // Valve closing pin

const unsigned long totalValveOpenTime = 8.5 * 15 * 1000;   // Total time required for full opening (8.5 mm * 15 seconds/mm)
const unsigned long stepValveTime = 8.5 * 15 * 1000 * 0.01; // We define a step of 1% of the total time required for full opening (1% of 8.5 mm * 15 seconds/mm)
unsigned int currentStep = 0;                               // Current step in the valve control algorithm, from 0 to 100

// Valve control pin initialization function
void setupValveControl()
{
    pinMode(PIN_VALVE_OPEN, OUTPUT);  // Set the opening valve pin as output
    pinMode(PIN_VALVE_CLOSE, OUTPUT); // Set the closing valve pin as output
}

// Valve opening function
void openValve()
{
    digitalWrite(PIN_VALVE_OPEN, HIGH);  // Open the valve
    digitalWrite(PIN_VALVE_CLOSE, LOW);  // Stop the valve
    Log.info("Opening valve..."); // Print to the serial monitor
}

// Valve closing function
void closeValve()
{
    digitalWrite(PIN_VALVE_CLOSE, HIGH); // Close the valve
    digitalWrite(PIN_VALVE_OPEN, LOW);   // Stop the valve
    Log.info("Closing valve..."); // Print to the serial monitor
}

// Valve stop function
void stopValve()
{
    digitalWrite(PIN_VALVE_OPEN, LOW);  // Stop the valve
    digitalWrite(PIN_VALVE_CLOSE, LOW); // Stop the valve
    Log.info("Stop valve...");   // Print to the serial monitor
}

void controlValve(unsigned int steps)
{
    int noOfSteps = steps - currentStep;
    if (noOfSteps > 0)
    {
        openValve();
        waitForSteps(noOfSteps);
        stopValve();
    }
    else if (noOfSteps < 0)
    {
        closeValve();
        waitForSteps(noOfSteps);
        stopValve();
    }
}

void waitForSteps(int steps)
{
    unsigned int stepsToMove = abs(steps);

    while (stepsToMove--)
    {
        delay(stepValveTime);

        if (steps > 0)
        {
            currentStep++;
        }
        else
        {
            currentStep--;
        }

        Log.info("Current step: %d", currentStep);
    }
}

// Valve calibration function
void calibrateValveOnStartup()
{

    if (!developDebug)
    {
        controlValve(100); // Open the valve to maximum

        controlValve(5); // Close the valve down to antefreeze point
    }
}

// Valve control anti freeze function ensuring that the valve is open at least 5%
void ensureAntiFreeze()
{
    controlValve(5);
}