#include "ForecastTemp.h"
#include <string>

SerialLogHandler logHandler;
const char *WEATHER_EVENT_NAME = "GetWeatherData";
int currentTime;
double currentTemp;
int hourTime[3];
double hourTemp[3];

void subscriptionHandler(const char *event, const char *data);

// SYSTEM_THREAD(ENABLED);

enum
{
    STATE_WAIT_FOR_CONNECTED,
    STATE_WAIT_TO_PUBLISH,
    STATE_IDLE
};
int state = STATE_WAIT_FOR_CONNECTED;
unsigned long stateTime;

void setupWeatherApi()
{
    // {{{PARTICLE_DEVICE_ID}}}/{{{PARTICLE_EVENT_NAME}}}
    String subscriptionName = String::format("%s/%s/", System.deviceID().c_str(), WEATHER_EVENT_NAME);
    Particle.subscribe(subscriptionName, subscriptionHandler, MY_DEVICES);
    Log.info("subscribing to %s", subscriptionName.c_str());
}

void readWeatherData()
{
    // switch (state)
    // {
    // case STATE_WAIT_FOR_CONNECTED:
    //     if (Particle.connected())
    //     {
    //         state = STATE_WAIT_TO_PUBLISH;
    //         stateTime = millis();
    //     }
    //     break;

    // case STATE_WAIT_TO_PUBLISH:
    //     if (millis() - stateTime >= 5000)
    //     {
    //         Particle.publish(WEATHER_EVENT_NAME, "", PRIVATE);
    //         state = STATE_IDLE;
    //     }
    //     break;

    // case STATE_IDLE:
    //     break;
    // }

    if (Particle.connected())
    {
        Particle.publish(WEATHER_EVENT_NAME, "", PRIVATE);
    }
}

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
                    currentTime = iter2.value().toInt();
                    Log.info("current dt=%d", iter2.value().toInt());
                }
                if (iter2.name() == "temp")
                {
                    currentTemp = iter2.value().toDouble();
                    Log.info("current temp=%lf", iter2.value().toDouble());
                }
            }
        }
        if (iter.name() == "hourly")
        {
            JSONArrayIterator iter2(iter.value());
            for (size_t ii = 0; iter2.next(); ii++)
            {
                Log.info("hourly array index %u", ii);
                JSONObjectIterator iter3(iter2.value());
                while (iter3.next())
                {
                    if (iter3.name() == "dt")
                    {
                        hourTime[ii] = iter3.value().toInt();
                        Log.info("dt=%d", iter3.value().toInt());
                    }
                    if (iter3.name() == "temp")
                    {
                        hourTemp[ii] = iter3.value().toDouble();
                        Log.info("temp=%lf", iter3.value().toDouble());
                    }
                }
            }
        }
    }
}
