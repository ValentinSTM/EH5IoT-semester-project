// SensorReading.h
#ifndef SENSOR_READING_H
#define SENSOR_READING_H

#include <Particle.h>

const int ANALOG_PIN = A0;           // PT500 connected to A0
const float REFERENCE_VOLTAGE = 3.3; // Reference voltage for Argon
const float ADC_MAX_VALUE = 4095.0;  // 12-bit ADC resolution
const float SERIES_RESISTOR = 596;   // Series resistor value

// Function to read the analog value from the sensor
float readSensor();

// Function to convert the analog value to resistance
float calculateResistance(int adcValue);

#endif
