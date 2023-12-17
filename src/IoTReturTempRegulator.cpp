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
#include "CollectData.h"
#include "RTDTable.h"
#include "ValveControl.h"
#include "PIDController.h"
#include "ForecastTemp.h"
#include "Common.h"

// Define PID constants
const double Kp = 5.0;                   // Proportional constant (adjust current error) (1.0)
const double Ki = 0.5;                   // Integral constant ( adjust past error) (0.1)
const double Kd = 0.01;                  // Derivative constant (adjust future error)  (0.01)
PIDController pidController(Kp, Ki, Kd); // Create a PIDController object with the PID constants

// Define collect interval
unsigned long lastCollectTime = 0;
const unsigned long collectInterval = 60000; // 60 seconds in miliseconds

// Define publish interval
unsigned long lastPublishTime = 0;
const unsigned long publishInterval = 1800000; // 30 minutes in miliseconds

// Define forecast interval
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

  // Collect data for logging
  if ((millis() - lastCollectTime >= forecastInterval))
  {
    lastCollectTime = millis();
    time32_t now = Time.now();
    LogData collectedData = {now, temperature, valveOutput};
    collectData(&collectedData); // Save the data
  }

  // Publish our data
  if ((millis() - lastPublishTime >= publishInterval) && connectToCloud)
  {
    lastPublishTime = millis();
    sendCollectData(); // Publish the collected data to the Particle Cloud
  }

  // Request weather data
  if ((millis() - lastForecastTime >= forecastInterval) && connectToCloud)
  {
    lastForecastTime = millis();
    readWeatherData(); // Read the weather API data

    updateSetpoint(forecastCurrentTemp); // Update the setpoint based on the current temperature in the latest weather data
  }

  delay(1000); // Delay for 1 second
}
