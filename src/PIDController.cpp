// PIDController.cpp
#include "PIDController.h"
#include "C:/Particle_iOT/EH5IoT-semester-project/lib/pid/src/pid.h"

// P = Proportional - Kp = Proportional constant (adjust current error)
// I = Integral - Ki = Integral constant ( adjust past error)
// D = Derivative - Kd = Derivative constant (adjust future error)

PIDController::PIDController(double Kp, double Ki, double Kd)
    : setpoint(0), input(0), output(0), Kp(Kp), Ki(Ki), Kd(Kd), pid(&input, &output, &setpoint, Kp, Ki, Kd, PID::DIRECT) {}

void PIDController::begin() // Start PID control and set mode to AUTOMATIC (PID::AUTOMATIC)
{
    pid.SetOutputLimits(-100, 100); // Set the output limits for the PID controller (valve output between 0 and 100%
    pid.SetMode(PID::AUTOMATIC);    // Set PID mode to AUTOMATIC
}

void PIDController::setSetpoint(double sp) // Set the setpoint for the PID controller to compute the output based on the input and setpoint values
{
    setpoint = sp; // Set the setpoint
}

void PIDController::setInput(double in) // Set the input for the PID controller to compute the output based on the input and setpoint values
{
    input = in; // Set the input
}

double PIDController::compute() // Compute the PID output based on the input and setpoint values
{
    pid.Compute(); // Compute the PID output based on the input and setpoint values
    return output; // Return the PID output
}

double PIDController::getOutput() // Get the PID output
{
    return output; // Return the PID output
}
