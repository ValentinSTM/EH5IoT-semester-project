// ForecastTemp.h
#ifndef FORECAST_TEMP_H
#define FORECAST_TEMP_H

#include "Particle.h"

void setupWeatherApi();
void subscriptionHandler(const char *event, const char *data);
void requestWeatherData();
void printWeatherData();

#endif /* FORECAST_TEMP_H */
