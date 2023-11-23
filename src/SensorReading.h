// SensorReading.h
#ifndef SENSOR_READING_H
#define SENSOR_READING_H

#include <Particle.h>

const int ANALOG_PIN = A0;           // PT500 connected to A0 pin on Photon2 (Analog pin) (ADC) (Analog to Digital Converter) (0-4095) (0-3.3V)
const float REFERENCE_VOLTAGE = 3.3; // Reference voltage for Argon (3.3V) (3.3V/4095=0.00080586V)
const float ADC_MAX_VALUE = 4095.0;  // 12-bit ADC resolution (4095) (2^12=4096) (0-4095) (0-3.3V)
const float SERIES_RESISTOR = 596;   // Series resistor value

// Function to read the analog value from the sensor
float readSensor();

// Function to convert the analog value to resistance
float calculateResistance(int adcValue);

#endif /* SENSOR_READING_H */
