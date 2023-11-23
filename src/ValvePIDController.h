// ValvePIDController.h
#ifndef VALVE_PID_CONTROLLER_H
#define VALVE_PID_CONTROLLER_H

// Define thresholds for valve action
const double pidUpperTrigger = 5;  // Threshold for opening the valve   (5)
const double pidLowerTrigger = -5; // Threshold for closing the valve (-5)
const double threshold = 1;        // Threshold for valve action (5)

void controlValveWithPID(double valveOutput, double currentTemperature); // PID output is between 0 (fully closed) and 100 (fully open)

void calibrateValveOnStartup(); // Function for calibrating the valve on startup

#endif /* VALVE_PID_CONTROLLER_H */
