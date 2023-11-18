// Communication.cpp
#include "Communication.h"

void publishTemperature(float temperature)
{
    Particle.publish("temperature", String(temperature), PRIVATE);
}
