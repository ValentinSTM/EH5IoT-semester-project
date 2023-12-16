// TempSensor.cpp
#include "TempSensor.h"
#include "DataProcessing.h"

std::deque<float> resistanceSamples; // Queue of resistance samples for moving average

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

    // Read the temperature from the PT500 sensor, and make an average of 10 samples
    for (int i = 0; i < noOfSamples; i++)
    {
        sumOfSamples += readTempSensor();
        delay(10);
    }

    int averageAdcValue = (int)(sumOfSamples / noOfSamples);
    float resistance = calculateResistance(averageAdcValue); // Calculate the resistance from the ADC value
    float temperature = interpolateTemperature(resistance);
    Log.info("Resistance: %f, temperature %f", resistance, temperature);

    // TODO fix this, decide where to put
    // Moving average for spikes over longer time.
    // static float sumOfSamplesMovingAverage = 0;
    // sumOfSamplesMovingAverage += resistance; // Add the resistance to the sum of the samples for the moving average calculation
    // // Serial.printlnf("Resistance: %f", resistance);    // Print the resistance to the serial monitor
    // Serial.printlnf("Sum of samples: %f", sumOfSamplesMovingAverage); // Print the sum of the samples to the serial monitor
    // resistanceSamples.push_back(resistance);             // Add the resistance to the resistance samples queue for the moving average calculation

    // // Process the data to get the temperature
    // float movingAverage = calculateMovingAverage(resistanceSamples, sumOfSamplesMovingAverage); // Calculate the moving average resistance value from the resistance samples queue and the sum of the samples for the moving average calculation
    // float temperatureMovingAverage = interpolateTemperature(movingAverage);                     // Interpolate the temperature from the RTD table using the moving average resistance value and the RTD table data

    return temperature;
}
