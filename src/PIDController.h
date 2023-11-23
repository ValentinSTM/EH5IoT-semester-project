// PIDController.h
#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

// Include the Particle library
#include <Particle.h>
#include "C:/Particle_iOT/EH5IoT-semester-project/lib/pid/src/pid.h" // Include the PID library

class PIDController // Create a PIDController class
{
public:                                             // Public functions and variables
    PIDController(double Kp, double Ki, double Kd); // Constructor for the PIDController class with the PID constants as arguments
    void begin();                                   // Start PID control and set mode to AUTOMATIC (PID::AUTOMATIC)
    void setSetpoint(double setpoint);              // Set the setpoint for the PID controller to compute the output based on the input and setpoint values
    void setInput(double input);                    // Set the input for the PID controller to compute the output based on the input and setpoint values
    double compute();                               // Compute the PID output based on the input and setpoint values
    double getOutput();                             // Get the PID output (valve output)

private:               // Private functions and variables
    double setpoint;   // Define the identifier 'setpoint'
    double input;      // Define the identifier 'input'
    double output;     // Define the identifier 'output'
    double Kp, Ki, Kd; // Define the identifiers 'Kp', 'Ki' and 'Kd'
    PID pid;           // Define the identifier 'PID' from the PID library
};

#endif
