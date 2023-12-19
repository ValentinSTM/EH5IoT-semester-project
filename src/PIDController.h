// PIDController.h
#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

// Include the Particle library
#include <Particle.h>
#include "../lib/pid/src/pid.h"

class PIDController // Create a PIDController class
{
public:
    PIDController(double Kp, double Ki, double Kd); // Constructor for the PIDController class with the PID constants as arguments
    void begin();                                   // Start PID control and set mode to AUTOMATIC (PID::AUTOMATIC)
    void setSetpoint(double setpoint);              // Set the setpoint for the PID controller to be used in computing the output
    void setInput(double input);                    // Set the input for the PID controller  to be used in computing the output
    bool compute();                                 // Compute the PID output based on the input and setpoint values
    double getOutput();                             // Get the PID output

private:
    double m_setpoint; // Define the identifier 'setpoint'
    double m_input;    // Define the identifier 'input'
    double m_output;   // Define the identifier 'output'
    double Kp, Ki, Kd; // Define the identifiers 'Kp', 'Ki' and 'Kd'
    PID m_pid;         // Define the identifier 'PID' from the PID library
};

#endif
