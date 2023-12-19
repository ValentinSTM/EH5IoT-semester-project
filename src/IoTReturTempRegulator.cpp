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

SYSTEM_THREAD(ENABLED); // Enable multi-threading

// Define PID constants
const double Kp = 5.0;                   // Proportional constant (adjust current error) (1.0)
const double Ki = 0.5;                   // Integral constant ( adjust past error) (0.1)
const double Kd = 0.01;                  // Derivative constant (adjust future error)  (0.01)
PIDController pidController(Kp, Ki, Kd); // Create a PIDController object with the PID constants

// Define collect interval
unsigned long lastCollectTime = 0;
const unsigned long collectInterval = 3600; // 1 hour in seconds

// Define publish interval
unsigned long lastPublishTime = 0;
const unsigned long publishInterval = 10800; // 3 hours in seconds

// Define forecast interval
unsigned long lastForecastTime = 0;
const unsigned long forecastInterval = 10800; // 3 hours in seconds

os_mutex_t valveMutex;

void setup()
{
  Serial.begin(9600);                      // Initialize the Serial monitor
  Log.info("Logging with LOG_LEVEL_INFO"); // Particle log level is INFO

  os_mutex_create(&valveMutex);

  setupTempSensor();

  forecastedData.resize(FORECAST_DATA_SIZE);
  setupWeatherApi();

  setupValveControl();
  calibrateValveOnStartup(); // Calibrate valve on startup (open fully and close)
  new Thread("ValveControlThread", valveControlThread);

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
  os_mutex_lock(valveMutex);
  valveOutput = pidController.getOutput();
  os_mutex_unlock(valveMutex);
  Log.info("Current Temp: %.2f, Setpoint: %.2f, Temp Diff: %.2f, Valve Output: %.2f",
           temperature, setpoint, (setpoint - temperature), valveOutput);

  // controlValve(valveOutput); // Control valve with output from PID controller, when not using a thread

  // Collect data for logging
  if ((Time.now() - lastCollectTime >= collectInterval))
  {
    lastCollectTime = Time.now();
    time32_t now = Time.now();
    LogData collectedData = {now, temperature, valveOutput};
    collectData(&collectedData); // Save the data
  }

  // Publish our data
  if ((Time.now() - lastPublishTime >= publishInterval) && connectToCloud)
  {
    lastPublishTime = Time.now();
    sendCollectData(); // Publish the collected data to the Particle Cloud
  }

  // Request weather data
  if ((Time.now() - lastForecastTime >= forecastInterval) && connectToCloud)
  {
    lastForecastTime = Time.now();
    requestWeatherData(); // Request to read the weather API data
  }

  if ((unsigned int)Time.now() - currentData.timestamp <= forecastInterval) // if the data is new, use received timestamp from forecast data
  {
    updateSetpoint(forecastedData[2].temperature); // Update the setpoint based on the current temperature in the latest weather data, use the 3rd hour forecast
  }

  delay(1000); // Delay for 1 second
}
