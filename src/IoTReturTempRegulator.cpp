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

#include "Particle.h" // Include Particle specific functions
#include "TempSensor.h"
#include "DataProcessing.h"
#include "Communication.h"
#include "RTDTable.h"
#include "ValveControl.h"
#include "PIDController.h"
#include "ForecastTemp.h"
#include "Common.h"

double setpoint = 30; // Define the identifier 'setpoint'

// Define PID constants
const double Kp = 5.0;                   // Proportional constant (adjust current error) (1.0)
const double Ki = 0.5;                   // Integral constant ( adjust past error) (0.1)
const double Kd = 0.01;                  // Derivative constant (adjust future error)  (0.01)
PIDController pidController(Kp, Ki, Kd); // Create a PIDController object with the PID constants

// Define publish interval
unsigned long lastPublishTime = 0;
const unsigned long publishInterval = 1800000; // 30 minutes in miliseconds

// int currentSteps = 0;                // Current step in the valve control algorithm
// const int totalStepsForOpen = 1000;  // Total number of steps to open the valve
// const int totalStepsForClose = 1000; // Total number of steps to close the valve

unsigned long lastForecastTime = 0;
const unsigned long forecastInterval = 60000; // 60 seconds in miliseconds

void setup()
{
  Serial.begin(9600); // Initialize the Serial monitor
  Log.info("Logging with LOG_LEVEL_INFO");

  setupTempSensor();
  setupWeatherApi();

  setupValveControl();
  calibrateValveOnStartup(); // Calibrate valve on startup (open fully and close)

  // Setup PID controller
  pidController.setSetpoint(setpoint); // Setpoint for return temperature (output)
  pidController.begin();               // Initialisering PIDController

  // TODO Delete this
  // Setup Particle Cloud communication
  // publishTemperature(); // Publish the temperature to the Particle Cloud
}

void loop()
{
  // Read the temperature from the PT500 sensor
  float temperature = getTempValue();

  // PID controller
  pidController.setInput((double)temperature); // Current temperature from PT500 sensor as input for PID controller
  pidController.compute();                     // Compute PID output

  // Control valve with PID output
  double valveOutput = pidController.getOutput();
  controlValve(valveOutput); // Control valve with output from PID controller
  Log.info("Current Temp: %.2f, Setpoint: %.2f, Temp Diff: %.2f, Valve Output: %.2f",
           temperature, setpoint, (setpoint - temperature), valveOutput);

  // Publish the data
  // Logging and publishing at 30 minute intervals of temperature and PID output to monitor the operation of the return temperature control system

  if (millis() - lastPublishTime >= publishInterval) // If the time since the last publish is greater than the publish interval
  {
    lastPublishTime = millis();                                                                        // Update the last publish time
    String data = String::format("Temperature: %.2f C, Valve Output: %.2f", temperature, valveOutput); // Format the data to be published
    // TODO add outside temperature
    // TODO change valve data to measure steps done in last period
    Log.info(data);                                        // Print the data to the serial monitor
    Particle.publish("temperature_update", data, PRIVATE); // Publish the data to the Particle Cloud

    // // Log the valve action based on the PID output and valve specifications
    // if (valveOutput > pidUpperTrigger) // If the valve output is greater than the upper trigger
    // {
    //   Serial.println("Valve action: open"); // Open the valve to increase the flow and effectively use the heat transfer in the room through the radiator
    // }
    // else if (valveOutput < pidLowerTrigger) // If the valve output is less than the lower trigger
    // {
    //   Serial.println("Valve action: close"); // Close the valve to reduce the flow and effectively use the heat transfer in the room through the radiator
    // }
    // else
    // {
    //   Serial.println("Valve action: hold"); // Hold the valve in the current position
    // }
  }

  if (millis() - lastForecastTime >= forecastInterval) // If the weather API data is read
  {
    lastForecastTime = millis();
    readWeatherData(); // Read the weather API data

    // TODO update setpoint based on  Logic for setpoint table in ValvePIDController.h
  }

  delay(1000); // Delay for 1 second
}
// Additional Notes:
// - The SERIAL_BUFFER_SIZE might need to be adjusted based on the requirements of your application.
// - Make sure to include your RTDTable and PT500Sensor libraries in the src/ directory.
// - Review and adhere to the guidelines for safely publishing events to the Particle Cloud.
