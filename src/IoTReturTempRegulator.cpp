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
#include "ValveControl.h"
#include "PIDController.h"
#include "ValvePIDController.h"

// Define PID constants
const double Kp = 1.0;  // Proportional constant (adjust current error)
const double Ki = 0.1;  // Integral constant ( adjust past error)
const double Kd = 0.01; // Derivative constant (adjust future error)

PIDController pidController(Kp, Ki, Kd); // Global scope

int currentSteps = 0;                // Current step in the valve control algorithm
const int totalStepsForOpen = 1000;  // Total number of steps to open the valve
const int totalStepsForClose = 1000; // Total number of steps to close the valve

std::deque<float> resistanceSamples; // Queue of resistance samples for moving average
float sumOfSamples = 0;              // Sum of resistance samples for moving average

void setup()
{
  pinMode(ANALOG_PIN, INPUT);
  Serial.begin(9600);
  // // Setup valve control
  setupValveControl();
  //   // // Setup PID controller
  pidController.setSetpoint(30.0); // Setpoint 30°C
  pidController.begin();           // Initialisering PIDController

  // Setup Particle Cloud communication
  publishTemperature(); // Publish the temperature to the Particle Cloud
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

  // Print the data to the Serial monitor for debugging
  Serial.printlnf("Resistance: %f Ohm, Temperature: %f C", movingAverage, temperature);

  // PID controller
  double currentTemperature = temperature;      /* read from PT500 */
  pidController.setInput(currentTemperature);   // Actual input from PT500
  double valveOutput = pidController.compute(); // Compute PID output

  // Control valve with PID output
  controlValveWithPID(valveOutput, currentTemperature);

  // Publish the data
  // publishTemperature(temperature); // oprita pentru a nu publica in cloud pana la finalizarea proiectului

  delay(1000);
}
// Additional Notes:
// - The SERIAL_BUFFER_SIZE might need to be adjusted based on the requirements of your application.
// - Make sure to include your RTDTable and PT500Sensor libraries in the src/ directory.
// - Review and adhere to the guidelines for safely publishing events to the Particle Cloud.
