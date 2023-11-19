// ValveControl.h
#ifndef VALVE_CONTROL_H
#define VALVE_CONTROL_H

void setupValveControl();
void openValve();
void closeValve();
void manualValveSetting();
void calibrateValve();
void controlValveWithPID(double pidOutput);
void initializeValvePosition();

#endif
