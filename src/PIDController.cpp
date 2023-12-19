// PIDController.cpp
#include "PIDController.h"

// P = Proportional - Kp = Proportional constant (adjust current error)
// I = Integral - Ki = Integral constant ( adjust past error)
// D = Derivative - Kd = Derivative constant (adjust future error)

PIDController::PIDController(double Kp, double Ki, double Kd)
    : m_setpoint(0), m_input(0), m_output(0), m_pid(&m_input, &m_output, &m_setpoint, Kp, Ki, Kd, PID::DIRECT)
{
}

void PIDController::begin()
{
    m_pid.SetOutputLimits(0, 100); // Set the output limits for the PID controller (valve output between 0 and 100%)
    m_pid.SetMode(PID::AUTOMATIC); // Set PID mode to AUTOMATIC
}

void PIDController::setSetpoint(double setpoint) // Set the setpoint for the PID controller to be used in computing the output
{
    m_setpoint = setpoint;
    Log.trace("Setpoint set to: %.2f", m_setpoint);
}

void PIDController::setInput(double input) // Set the input for the PID controller to be used in computing the output
{
    m_input = input;
    Log.trace("Input set to: %.2f", m_input);
}

bool PIDController::compute() // Compute the PID output based on the input and setpoint values
{
    return m_pid.Compute();
}

double PIDController::getOutput() // Get the PID output
{
    return m_output;
}
