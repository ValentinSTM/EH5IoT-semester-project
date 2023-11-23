// ValveControl.h
#ifndef VALVE_CONTROL_H
#define VALVE_CONTROL_H

/**
 * @brief Function for calibrating the valve.
 *
 * This function is used to calibrate the valve and ensure its proper functioning.
 * It should be called before using the valve for any operation.
 */
void calibrateValve(); // Function for calibrating the valve

void setupValveControl(); // Function for initializing the valve control pins
void openValve();         // Function for opening the valve
void closeValve();        // Function for closing the valve
void stopValve();         // Function for stopping the valve

#endif /* VALVE_CONTROL_H */
