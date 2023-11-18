// PIDController.h
#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

// Include the Particle library
#include <Particle.h>
#include "lib/pid/src/pid.h"

class PIDController
{
public:
    PIDController(double Kp, double Ki, double Kd);
    void begin();
    void setSetpoint(double setpoint);
    void setInput(double input);
    double compute();
    double getOutput();

private:
    double setpoint;
    double input;
    double output;
    double Kp, Ki, Kd;
    PID pid; // Define the identifier 'PID'
};

#endif
