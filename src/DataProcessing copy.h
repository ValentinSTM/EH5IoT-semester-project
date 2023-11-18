// DataProcessing.h
#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

#include <deque>

const size_t SAMPLE_SIZE = 5; // Number of samples for averaging

// Function to calculate the moving average of resistance
float calculateMovingAverage(std::deque<float> &resistanceSamples, float &sumOfSamples);

// Function to interpolate temperature from resistance
float interpolateTemperature(float measuredResistance);

#endif
