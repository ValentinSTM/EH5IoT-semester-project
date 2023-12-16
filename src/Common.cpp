// Common.cpp
#include "Common.h"
#include "Particle.h"

bool developDebug = true;
SerialLogHandler logHandler(LOG_LEVEL_INFO); // During development INFO, change to LOG_LEVEL_WARN or LOG_LEVEL_ERROR for production

const char *WEATHER_EVENT_NAME = "GetWeatherData";
int forecastCurrentTime;
double forecastCurrentTemp;
int forecastHourTime[3];
double forecastHourTemp[3];