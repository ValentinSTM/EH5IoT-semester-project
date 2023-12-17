// Common.h

#ifndef COMMON_H
#define COMMON_H

extern bool enableCalibration;
extern bool connectToCloud;

extern double setpoint;

extern const char *WEATHER_EVENT_NAME;
extern const char *COLLECTED_DATA_EVENT_NAME;
extern int forecastCurrentTime;
extern double forecastCurrentTemp;
extern int forecastHourTime[3];
extern double forecastHourTemp[3];


void updateSetpoint(double temperature);

#endif /* COMMON_H */