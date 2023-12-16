// ValveControl.h
#ifndef VALVE_CONTROL_H
#define VALVE_CONTROL_H

/*
Logic for setpoint. This is dynamic depending on the outside temperature.
------------------------------------------------------------------
| Extreme low temperature | Low temperature | Normal temperature |
------------------------------------------------------------------
| < -3°C                  | -2°C to 2°C     | > 3°C              |
------------------------------------------------------------------
| Set point 40°C          | Set point 35°C  | Set point 30°C     |
------------------------------------------------------------------

Valve control
M3P 468x5-3x = 15 s/mm

Valve control logic for setpoint 30°C. NOT VALID ANYMORE
Temperature difference is calculated as the difference between the setpoint and the current temperature.
-------------------------------------------------------------------------------------------
| Temperature diff > 2°C | Temperature diff between -2°C and 2°C | Temperature diff < -2°C |
|                        | Controlled by treshold                |                         |
--------------------------------------------------------------------------------------------
| Open valve             | Do nothing                            | Close valve             |

*/


void setupValveControl();              // Function for initializing the valve control pins
void openValve();                      // Function for opening the valve
void closeValve();                     // Function for closing the valve
void stopValve();                      // Function for stopping the valve
void controlValve(unsigned int steps); // Function for controlling the valve
void waitForSteps(int steps);          // Function for waiting for a number of steps. Uses delay
void calibrateValveOnStartup();        // Function for calibrating the valve on startup
void ensureAntiFreeze();               // Function for ensuring anti freeze

#endif /* VALVE_CONTROL_H */
