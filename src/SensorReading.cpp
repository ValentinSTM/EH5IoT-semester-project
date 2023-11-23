// SensorReading.cpp
#include "SensorReading.h" // Include the SensorReading header file

float readSensor() // Function to read the analog value from the sensor
{
    return analogRead(ANALOG_PIN); // Read the analog value from the sensor
}

float calculateResistance(int adcValue) // Function to convert the analog value to resistance
{
    float voltage = (adcValue / ADC_MAX_VALUE) * REFERENCE_VOLTAGE; // Calculate the voltage from the ADC value
    return SERIES_RESISTOR / ((REFERENCE_VOLTAGE / voltage) - 1.0); // Calculate the resistance from the voltage
}
