#ifndef VALVE_PID_CONTROLLER_H
#define VALVE_PID_CONTROLLER_H

const double threshold = 50; // Ajustați această valoare conform nevoilor
void controlValveWithPID(double valveOutput, double currentTemperature);

#endif
