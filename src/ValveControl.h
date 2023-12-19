// ValveControl.h
#ifndef VALVE_CONTROL_H
#define VALVE_CONTROL_H

void setupValveControl();              // Function for initializing the valve control pins
void openValve();                      // Function for opening the valve
void closeValve();                     // Function for closing the valve
void stopValve();                      // Function for stopping the valve
void valveControlThread(void);         // Function for controlling the valve in a thread
void controlValve(unsigned int steps); // Function for controlling the valve
void waitForSteps(int steps);          // Function for waiting for a number of steps. Uses delay
void calibrateValveOnStartup();        // Function for calibrating the valve on startup
void ensureAntiFreeze();               // Function for ensuring anti freeze

#endif /* VALVE_CONTROL_H */
