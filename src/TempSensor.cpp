// TempSensor.cpp
#include "TempSensor.h"
#include "RTDTable.h" // Include the RTD Table module header file
#include <algorithm>  // Add this to include the standard algorithms library

std::deque<float> temperatureSamples; // Queue of resistance samples for moving average

void setupTempSensor()
{
    pinMode(ANALOG_PIN, INPUT); // Set an analog pin (A0) as an input pin for the ADC (Analog to Digital Converter) to read the sensor data from the PT500 RTD sensor (resistance)
}

int readTempSensor()
{
    return analogRead(ANALOG_PIN); // Read the analog value from the sensor
}

float calculateResistance(int adcValue) // Function to convert the analog value to resistance
{
    float voltage = (adcValue / ADC_MAX_VALUE) * REFERENCE_VOLTAGE; // Calculate the voltage from the ADC value
    return SERIES_RESISTOR / ((REFERENCE_VOLTAGE / voltage) - 1.0); // Calculate the resistance from the voltage
}

float getTempValue()
{
    int sumOfSamples = 0;
    int noOfSamples = 10;

    // Read the temperature from the PT500 sensor, and make an average of 10 samples to get a stable reading
    for (int i = 0; i < noOfSamples; i++)
    {
        sumOfSamples += readTempSensor();
        delay(10);
    }

    int averageAdcValue = (int)(sumOfSamples / noOfSamples);
    float resistance = calculateResistance(averageAdcValue);
    float temperature = interpolateTemperature(resistance);
    Log.info("Current Resistance: %.2f, temperature %.2f", resistance, temperature);

    // Moving average for spikes over longer time periods
    // temperatureSamples.push_back(temperature); // add the resistance to the resistance samples queue for the moving average calculation
    float averaged_temperature = calculateMovingAverage(temperature);
    Log.info("Averaged temperature: %.2f", averaged_temperature);

    return averaged_temperature;
}

// Function to calculate the moving average of resistance samples
float calculateMovingAverage(float newTempSample)
{
    static float sumOfSamples = 0;

    if (temperatureSamples.size() >= MOVING_AVERAGE_SAMPLE_SIZE) // If the number of samples is greater than the sample size
    {
        sumOfSamples -= temperatureSamples.front(); // Subtract the first element in the queue from the sum of the samples
        temperatureSamples.pop_front();             // Remove the first element in the queue
    }

    temperatureSamples.push_back(newTempSample); // Add the new sample to the queue
    sumOfSamples += newTempSample;               // Add the new sample to the sum

    if (temperatureSamples.empty())
    {
        return 0; // If the queue is empty, average is 0
    }
    else
    {
        return sumOfSamples / temperatureSamples.size(); // Calculate the moving average of the temperature samples
    }
}

// Function to interpolate temperature from resistance using the RTD table
float interpolateTemperature(float measuredResistance)
{
    // Find the first element in the table that is greater than the measured resistance
    auto it = std::upper_bound(rtdTable, rtdTable + rtdTableSize, measuredResistance,
                               [](float a, const RtdValue &b)
                               { return a < b.resistance; }); // a is measured_resistance, b is the RtdValue struct in the table

    if (it == rtdTable + rtdTableSize) // If the measured resistance is greater than the last element in the table
    {
        return rtdTable[rtdTableSize - 1].temperature; // return the temperature of the last element in the table
    }

    if (it == rtdTable) // If the measured resistance is smaller than the first element in the table
    {
        return rtdTable[0].temperature; // return the temperature of the first element in the table
    }

    RtdValue upper = *it;     // upper is the first element in the table that is greater than the measured resistance
    RtdValue lower = *(--it); // lower is the element before upper

    return lower.temperature + (upper.temperature - lower.temperature) *
                                   (measuredResistance - lower.resistance) / (upper.resistance - lower.resistance); // Linear interpolation between lower and upper element in the table
}
