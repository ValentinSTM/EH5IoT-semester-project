// SensorReading.cpp
#include "SensorReading.h"

float readSensor()
{
    return analogRead(ANALOG_PIN);
}

float calculateResistance(int adcValue)
{
    float voltage = (adcValue / ADC_MAX_VALUE) * REFERENCE_VOLTAGE;
    return SERIES_RESISTOR / ((REFERENCE_VOLTAGE / voltage) - 1.0);
}
