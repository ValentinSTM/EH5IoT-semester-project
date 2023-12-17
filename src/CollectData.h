// CollectData.h
#ifndef COLLECT_DATA_H
#define COLLECT_DATA_H

#include <Particle.h>
#include "Common.h"

void collectData(LogData *logData);
void sendCollectData();
void publishCollectedData(const char *eventData);

#endif /* COLLECT_DATA_H */
