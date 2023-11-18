/**
 * Project: IoT Return Temperature Regulator
 * Author: Valentin-Stefan Tudora-Mayer
 * Date: [Project Start Date or Last Updated Date]
 * Description:
 * This firmware is designed for the Particle Photon 2 platform and enables the reading of
 * temperature data from a PT500 RTD sensor. It uses a moving average resistance calculation
 * to improve the stability of the temperature readings. The temperature is then published to
 * the Particle Cloud at a set interval.
 *
 * For more information on Particle's firmware API, visit:
 * https://docs.particle.io/reference/device-os/firmware/photon/
 */

// Include necessary libraries
#include "Particle.h"
#include "SensorReading.h"
#include "DataProcessing.h"
#include "Communication.h"
#include "RTDTable.h"

std::deque<float> resistanceSamples; // Queue of resistance samples for moving average
float sumOfSamples = 0;              // Sum of resistance samples for moving average

void setup()
{
  pinMode(ANALOG_PIN, INPUT);
  Serial.begin(9600);
}

void loop()
{
  // Read and process sensor data
  int adcValue = readSensor();
  float resistance = calculateResistance(adcValue);
  sumOfSamples += resistance;
  resistanceSamples.push_back(resistance);

  // Process the data to get the temperature
  float movingAverage = calculateMovingAverage(resistanceSamples, sumOfSamples);
  float temperature = interpolateTemperature(movingAverage);

  // Publish the data
  publishTemperature(temperature);

  // Print the data to the Serial monitor for debugging
  Serial.printlnf("Resistance: %f Ohm, Temperature: %f C", movingAverage, temperature);

  // Delay for 1 hour
  delay(3600000);
}

// Additional Notes:
// - The SERIAL_BUFFER_SIZE might need to be adjusted based on the requirements of your application.
// - Make sure to include your RTDTable and PT500Sensor libraries in the src/ directory.
// - Review and adhere to the guidelines for safely publishing events to the Particle Cloud.
