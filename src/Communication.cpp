// Communication.cpp
#include "Communication.h"

void publishTemperature(float temperature) // Function to publish temperature data to Particle cloud (https://docs.particle.io/reference/device-os/firmware/photon/#particle-publish-)
{
    Particle.publish("temperature", String(temperature), PRIVATE); // Publish the temperature to the Particle Cloud
}
