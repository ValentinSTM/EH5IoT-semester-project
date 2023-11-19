#include "ValvePIDController.h"
#include "ValveControl.h"
#include <cmath>      // Pentru fabs()
#include "Particle.h" // În cazul în care sunt necesare alte biblioteci specifice platformei sau proiectului

const double TemperatureChangeTrigger = 2.5;      // Definiți X ca schimbarea de temperatură pentru a declanșa ajustarea valvei
const double AllowedTemperatureFluctuation = 1.5; // Fluctuații de temperatură admise în grade Celsius
double previousTemperature = -1;                  // Inițializat la o valoare imposibilă pentru prima citire

void controlValveWithPID(double valveOutput, double currentTemperature)
{
    if (previousTemperature < 0)
    {
        previousTemperature = currentTemperature; // Setează prima temperatură citită
    }

    double temperatureDifference = fabs(currentTemperature - previousTemperature);

    // Decide dacă să ajusteze valva bazat pe schimbarea temperaturii
    if (temperatureDifference >= TemperatureChangeTrigger ||
        temperatureDifference > AllowedTemperatureFluctuation)
    {

        // Logică de ajustare a valvei bazată pe valveOutput și specificațiile valvei
        // De exemplu, dacă valveOutput este mare, poate deschideți mai mult valva, și invers
        if (valveOutput > threshold)
        {
            openValve(); // Deschide valva pentru a crește temperatura
        }
        else
        {
            closeValve(); // Închide valva pentru a scădea temperatura
        }

        previousTemperature = currentTemperature; // Actualizează temperatura precedentă
    }

    // Pentru debugging
    Serial.printlnf("Current Temp: %f, Previous Temp: %f, Temp Difference: %f, Valve Output: %f", currentTemperature, previousTemperature, temperatureDifference, valveOutput);
}
