// RTDTable.h
#ifndef RTD_TABLE_H
#define RTD_TABLE_H

struct RtdValue
{
    float temperature; // Temperature in degrees Celsius (°C) (°C = °K - 273.15) (°F = °C * 1.8 + 32)
    float resistance;  // Resistance in Ohms (Ω)
};

extern const RtdValue rtdTable[]; // RTD table of temperature and resistance values
extern const int rtdTableSize;    // Size of the RTD table

#endif /* RTD_TABLE_H */
