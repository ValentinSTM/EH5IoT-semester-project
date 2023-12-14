#include "Particle.h"

extern const char *WEATHER_EVENT_NAME;
extern int currentTime;
extern double currentTemp;
extern int hourTime[3];
extern double hourTemp[3];

void setupWeatherApi();
void subscriptionHandler(const char *event, const char *data);
void readWeatherData();