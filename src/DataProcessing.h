// DataProcessing.h
#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

#include <deque> // For using std::deque (double-ended queue) for storing resistance samples for moving average calculation (https://en.cppreference.com/w/cpp/container/deque)

const size_t SAMPLE_SIZE = 5; // Number of samples for averaging (moving average)

// Function to calculate the moving average of resistance samples
float calculateMovingAverage(std::deque<float> &resistanceSamples, float &sumOfSamples);

// Function to interpolate temperature from resistance using the RTD table
float interpolateTemperature(float measuredResistance);

#endif /* DATA_PROCESSING_H */
