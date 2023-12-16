// TempSensor.h
#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include <Particle.h>

const int ANALOG_PIN = A0;           // PT500 connected to A0 pin on Photon2 (Analog pin) (ADC) (Analog to Digital Converter) (0-4095) (0-3.3V)
const float REFERENCE_VOLTAGE = 3.3; // Reference voltage for Argon (3.3V) (3.3V/4095=0.00080586V)
const float ADC_MAX_VALUE = 4095.0;  // 12-bit ADC resolution (4095) (2^12=4096) (0-4095) (0-3.3V)
const float SERIES_RESISTOR = 596;   // Series resistor value

void setupTempSensor();
int readTempSensor();                    // Function to read the analog value from the sensor
float calculateResistance(int adcValue); // Function to convert the analog value to resistance
float getTempValue();                    // Function to get the temperature from the PT500 sensor, after being calculated and averaged

#endif /* TEMP_SENSOR_H */
