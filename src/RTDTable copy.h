// RTDTable.h
#ifndef RTD_TABLE_H
#define RTD_TABLE_H

struct RtdValue
{
    float temperature;
    float resistance;
};

extern const RtdValue rtdTable[];
extern const int rtdTableSize;

#endif
