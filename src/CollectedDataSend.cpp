// CollectedDataSend.cpp
#include "CollectedDataSend.h"
#include "Common.h"

void publishCollectedData(const char *eventData) // Function to publish data to Particle cloud (https://docs.particle.io/reference/device-os/firmware/photon/#particle-publish-)
{
    if (Particle.connected())
    {
        Log.info("Event (%s) data sent: %s", COLLECTED_DATA_EVENT_NAME, eventData);
        Particle.publish(COLLECTED_DATA_EVENT_NAME, eventData, PRIVATE);
    }
}
