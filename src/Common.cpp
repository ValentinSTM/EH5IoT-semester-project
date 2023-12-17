// Common.cpp
#include "Common.h"
#include "Particle.h"

bool enableCalibration = false;              // Set to true in production. Calibration takes long time, and can be disabled during development
bool connectToCloud = false;                 // Set to true in production. Prevent sending too many requests to the cloud during development
SerialLogHandler logHandler(LOG_LEVEL_INFO); // During development INFO, change to LOG_LEVEL_WARN or LOG_LEVEL_ERROR for production

double setpoint = 30; // Default value for setpoint

const char *WEATHER_EVENT_NAME = "GetWeatherForecast";
const char *COLLECTED_DATA_EVENT_NAME = "SendCollectedData";
int forecastCurrentTime;
double forecastCurrentTemp;
int forecastHourTime[3];
double forecastHourTemp[3];

/*
Function to update the setpoint.
Logic for setpoint is dynamic depending on the outside temperature.
------------------------------------------------------------------
| Extreme low temperature | Low temperature | Normal temperature |
------------------------------------------------------------------
| < -3°C                  | -2°C to 2°C     | > 3°C              |
------------------------------------------------------------------
| Set point 40°C          | Set point 35°C  | Set point 30°C     |
------------------------------------------------------------------
*/
void updateSetpoint(double temperature)
{
    double oldSetpoint = setpoint;

    if (temperature < -3)
    {
        setpoint = 40;
    }
    else if (temperature >= -2 && temperature <= 2)
    {
        setpoint = 35;
    }
    else if (temperature > 3)
    {
        setpoint = 30;
    }

    if (oldSetpoint != setpoint)
    {
        Log.info("Global setpoint set to: %.2f", setpoint);
    }
}
