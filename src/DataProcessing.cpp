// DataProcessing.cpp
#include "DataProcessing.h" // Include the DataProcessing header file
#include "RTDTable.h"       // Include the RTD Table module header file
#include <algorithm>        // Add this to include the standard algorithms library
#include <deque>            // Add this to include the double-ended queue library

// Function to calculate the moving average of resistance samples
float calculateMovingAverage(std::deque<float> &resistanceSamples, float &sumOfSamples)
{
    if (resistanceSamples.size() > SAMPLE_SIZE) // If the number of samples is greater than the sample size

    {
        sumOfSamples -= resistanceSamples.front(); // Subtract the first element in the queue from the sum of the samples for the moving average calculation
        resistanceSamples.pop_front();             // Remove the first element in the queue (first in, first out)
    }
    return resistanceSamples.empty() ? 0 : sumOfSamples / static_cast<float>(resistanceSamples.size()); // Calculate the moving average of the resistance samples
}

// Function to interpolate temperature from resistance using the RTD table
float interpolateTemperature(float measuredResistance)
{
    // Find the first element in the table that is greater than the measured resistance
    auto it = std::upper_bound(rtdTable, rtdTable + rtdTableSize, measuredResistance,
                               [](float a, const RtdValue &b)
                               { return a < b.resistance; }); // a is measured_resistance, b is the RtdValue struct in the table

    if (it == rtdTable + rtdTableSize) // If the measured resistance is greater than the last element in the table
    {
        return rtdTable[rtdTableSize - 1].temperature; // return the temperature of the last element in the table
    }

    if (it == rtdTable) // If the measured resistance is smaller than the first element in the table
    {
        return rtdTable[0].temperature; // return the temperature of the first element in the table
    }

    RtdValue upper = *it;     // upper is the first element in the table that is greater than the measured resistance
    RtdValue lower = *(--it); // lower is the element before upper

    return lower.temperature + (upper.temperature - lower.temperature) *
                                   (measuredResistance - lower.resistance) / (upper.resistance - lower.resistance); // Linear interpolation between lower and upper element in the table
}