// DataProcessing.cpp
#include "DataProcessing.h"
#include "RTDTable.h" // Include the RTD Table module header
#include <algorithm>  // Add this to include the standard algorithms library

float calculateMovingAverage(std::deque<float> &resistanceSamples, float &sumOfSamples)
{
    if (resistanceSamples.size() > SAMPLE_SIZE)
    {
        sumOfSamples -= resistanceSamples.front();
        resistanceSamples.pop_front();
    }
    return resistanceSamples.empty() ? 0 : sumOfSamples / static_cast<float>(resistanceSamples.size());
}

float interpolateTemperature(float measuredResistance)
{
    // Find the first element in the table that is greater than the measured resistance
    auto it = std::upper_bound(rtdTable, rtdTable + rtdTableSize, measuredResistance,
                               [](float a, const RtdValue &b)
                               { return a < b.resistance; }); // a is measured_resistance, b is the RtdValue

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