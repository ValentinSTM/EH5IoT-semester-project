// Common.h

#ifndef COMMON_H
#define COMMON_H

extern bool developDebug; // Flag to skip the valve calibration, only used during development

extern const char *WEATHER_EVENT_NAME;
extern int forecastCurrentTime;
extern double forecastCurrentTemp;
extern int forecastHourTime[3];
extern double forecastHourTemp[3];

#endif /* COMMON_H */