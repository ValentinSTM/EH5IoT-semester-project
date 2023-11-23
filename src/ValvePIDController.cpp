// ValvePIDController.cpp

#include "ValvePIDController.h"
#include "ValveControl.h"
#include <cmath> // For the fabs() function
#include "Particle.h"
#include "application.h"

extern double setpoint; // Setpoint temperature, defined elsewhere
// const double threshold = 5.0; // Threshold for additional control

const double TemperatureChangeTrigger = 1.0;
const double AllowedTemperatureFluctuation = 0.5;
double previousTemperature = -1.0;

void controlValveWithPID(double valveOutput, double currentTemperature)
{
    if (previousTemperature < 0)
    {
        previousTemperature = currentTemperature;
    }

    double temperatureDifference = fabs(currentTemperature - previousTemperature);

    if (temperatureDifference >= TemperatureChangeTrigger ||
        temperatureDifference > AllowedTemperatureFluctuation)
    {

        // Direct temperature error control
        double temperatureError = setpoint - currentTemperature;

        // Check if the temperature is significantly higher than setpoint
        if (temperatureError > threshold)
        {
            closeValve();
            Serial.println("Closing valve due to high temperature...");
        }
        // Check if the temperature is significantly lower than setpoint
        else if (temperatureError < -threshold)
        {
            openValve();
            Serial.println("Opening valve due to low temperature...");
        }
        // Use PID output for fine control
        else
        {
            if (valveOutput > pidUpperTrigger)
            {
                closeValve();
            }
            else if (valveOutput < pidLowerTrigger)
            {
                openValve();
            }
        }

        previousTemperature = currentTemperature;
    }

    Serial.printlnf("Current Temp: %.2f, Setpoint: %.2f, Temp Error: %.2f, Valve Output: %.2f",
                    currentTemperature, setpoint, temperatureDifference, valveOutput);
}
