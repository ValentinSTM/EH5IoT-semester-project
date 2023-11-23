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
#include "Particle.h"           // Include Particle specific functions
#include "SensorReading.h"      // Include the SensorReading library
#include "DataProcessing.h"     // Include the DataProcessing library
#include "Communication.h"      // Include the Communication library
#include "RTDTable.h"           // Include the RTDTable library
#include "ValveControl.h"       // Include the ValveControl library
#include "PIDController.h"      // Include the PIDController library
#include "ValvePIDController.h" // Include the ValvePIDController library

double setpoint = 25; // Define the identifier 'setpoint'

// Define PID constants
const double Kp = 5.0;  // Proportional constant (adjust current error) (1.0)
const double Ki = 0.5;  // Integral constant ( adjust past error) (0.1)
const double Kd = 0.01; // Derivative constant (adjust future error)  (0.01)

// Define publish interval
unsigned long lastPublishTime = 0;
const unsigned long publishInterval = 1800000; // 30 minute în milisecunde

PIDController pidController(Kp, Ki, Kd); // Create a PIDController object with the PID constants

// int currentSteps = 0;                // Current step in the valve control algorithm
// const int totalStepsForOpen = 1000;  // Total number of steps to open the valve
// const int totalStepsForClose = 1000; // Total number of steps to close the valve

std::deque<float> resistanceSamples; // Queue of resistance samples for moving average
float sumOfSamples = 0;              // Sum of resistance samples for moving average

void setup()
{
  // Set the analog pin as an input pin for the ADC (Analog to Digital Converter) to read the sensor data from the PT500 RTD sensor (resistance)
  pinMode(ANALOG_PIN, INPUT);

  Serial.begin(9600); // Initialize the Serial monitor

  // Setup valve control
  setupValveControl();

  // Setup PID controller
  // setpoint = 25.0;                     // Setpoint setting (input) (25°C return temperature)
  pidController.setSetpoint(setpoint); // Setpoint 25°C return temperature (output)
  pidController.begin();               // Initialisering PIDController

  // Calibrate valve on startup (initialization)
  calibrateValveOnStartup();

  // Setup Particle Cloud communication
  // publishTemperature(); // Publish the temperature to the Particle Cloud
}

void loop()
{
  // Read and process sensor data
  int adcValue = readSensor();                      // Read the sensor data from the ADC
  float resistance = calculateResistance(adcValue); // Calculate the resistance from the ADC value
  sumOfSamples += resistance;                       // Add the resistance to the sum of the samples for the moving average calculation
  resistanceSamples.push_back(resistance);          // Add the resistance to the resistance samples queue for the moving average calculation

  // Process the data to get the temperature
  float movingAverage = calculateMovingAverage(resistanceSamples, sumOfSamples); // Calculate the moving average resistance value from the resistance samples queue and the sum of the samples for the moving average calculation
  float temperature = interpolateTemperature(movingAverage);                     // Interpolate the temperature from the RTD table using the moving average resistance value and the RTD table data

  // Print the data to the Serial monitor for debugging
  // Serial.printlnf("Resistance: %2f Ohm, Temperature: %2f C", movingAverage, temperature);

  // PID controller
  double currentTemperature = temperature;      // Current temperature from PT500 sensor (input)
  pidController.setInput(currentTemperature);   // Actual input from PT500 sensor (input)
  double valveOutput = pidController.compute(); // Compute PID output (valve output)

  // Control valve with PID output
  controlValveWithPID(valveOutput, currentTemperature);

  // Publish the data
  // Logging and publishing at 30 minute intervals of temperature and PID output to monitor the operation of the return temperature control system

  if (millis() - lastPublishTime >= publishInterval) // If the time since the last publish is greater than the publish interval
  {
    lastPublishTime = millis();                                                                               // Update the last publish time
    String data = String::format("Temperature: %.2f C, Valve Output: %.2f", currentTemperature, valveOutput); // Format the data to be published
    Serial.println(data);                                                                                     // Print the data to the serial monitor
    Particle.publish("temperature_update", data, PRIVATE);                                                    // Publish the data to the Particle Cloud

    // Log the valve action based on the PID output and valve specifications
    if (valveOutput > pidUpperTrigger) // If the valve output is greater than the upper trigger
    {
      Serial.println("Valve action: open"); // Open the valve to increase the flow and effectively use the heat transfer in the room through the radiator
    }
    else if (valveOutput < pidLowerTrigger) // If the valve output is less than the lower trigger
    {
      Serial.println("Valve action: close"); // Close the valve to reduce the flow and effectively use the heat transfer in the room through the radiator
    }
    else
    {
      Serial.println("Valve action: hold"); // Hold the valve in the current position
    }
  }

  delay(1000); // Delay for 1 second
}
// Additional Notes:
// - The SERIAL_BUFFER_SIZE might need to be adjusted based on the requirements of your application.
// - Make sure to include your RTDTable and PT500Sensor libraries in the src/ directory.
// - Review and adhere to the guidelines for safely publishing events to the Particle Cloud.
