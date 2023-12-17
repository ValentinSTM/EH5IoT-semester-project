// Common.h

#ifndef COMMON_H
#define COMMON_H

#include <Particle.h>
#include <deque>

extern bool enableCalibration;
extern bool connectToCloud;

extern double setpoint;

extern const char *WEATHER_EVENT_NAME;
extern const char *COLLECTED_DATA_EVENT_NAME;

extern int forecastCurrentTime;
extern double forecastCurrentTemp;
extern int forecastHourTime[3];
extern double forecastHourTemp[3];

struct LogData
{
    time32_t timestamp;
    double temperature;
    double valveOutput;
};
const size_t LOGGED_DATA_SIZE = 3;
extern std::deque<LogData> logData;

void updateSetpoint(double temperature);

#endif /* COMMON_H */