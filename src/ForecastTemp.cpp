#include "ForecastTemp.h"
#include "Common.h"
#include <string>


void setupWeatherApi()
{
    String subscriptionName = String::format("%s/%s/", System.deviceID().c_str(), WEATHER_EVENT_NAME);  // {{{PARTICLE_DEVICE_ID}}}/{{{PARTICLE_EVENT_NAME}}}
    Particle.subscribe(subscriptionName, subscriptionHandler, MY_DEVICES);
    Log.info("subscribing to %s", subscriptionName.c_str());
}

void readWeatherData()
{
    if (Particle.connected())
    {
        Particle.publish(WEATHER_EVENT_NAME, "", PRIVATE);
    }
}

// Function to decode the data
// Format is the following:
//  {"current": {"dt":{{current.dt}}, "temp":{{current.temp}}},
// "hourly":[{"dt":{{hourly.0.dt}},"temp":{{hourly.0.temp}}},
// {"dt":{{hourly.1.dt}},"temp":{{hourly.1.temp}}},
// {"dt":{{hourly.2.dt}},"temp":{{hourly.2.temp}}}]}
void subscriptionHandler(const char *event, const char *data)
{
    JSONValue outerObj = JSONValue::parseCopy(data);
    JSONObjectIterator iter(outerObj);
    while (iter.next())
    {
        if (iter.name() == "current")
        {
            JSONObjectIterator iter2(iter.value());
            while (iter2.next())
            {
                if (iter2.name() == "dt")
                {
                    forecastCurrentTime = iter2.value().toInt();
                    Log.trace("current dt=%d", iter2.value().toInt());
                }
                if (iter2.name() == "temp")
                {
                    forecastCurrentTemp = iter2.value().toDouble();
                    Log.trace("current temp=%lf", iter2.value().toDouble());
                }
            }
        }
        if (iter.name() == "hourly")
        {
            JSONArrayIterator iter2(iter.value());
            for (size_t ii = 0; iter2.next(); ii++)
            {
                Log.trace("hourly array index %u", ii);
                JSONObjectIterator iter3(iter2.value());
                while (iter3.next())
                {
                    if (iter3.name() == "dt")
                    {
                        forecastHourTime[ii] = iter3.value().toInt();
                        Log.trace("dt=%d", iter3.value().toInt());
                    }
                    if (iter3.name() == "temp")
                    {
                        forecastHourTemp[ii] = iter3.value().toDouble();
                        Log.trace("temp=%lf", iter3.value().toDouble());
                    }
                }
            }
        }
    }

    printWeatherData(); // Pretty print the received weather data
}

void printWeatherData()
{
    Log.info("Weather forecast received, currentTime: %d, currentTemp %lf C", forecastCurrentTime, forecastCurrentTemp);                                                                                                    // Print the weather API data to the serial monitor
    for (int i = 0; i < 3; i++)
    {
        Log.info("Weather forecast received, hour %d Time: %d, hour %d Temp %lf C", i + 1, forecastHourTime[i], i + 1, forecastHourTemp[i]);                                                                                                                    // Print the weather API data to the serial monitor
    }
}
