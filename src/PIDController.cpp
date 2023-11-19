// PIDController.cpp
#include "PIDController.h"

#include "lib/pid/src/pid.h"

PIDController::PIDController(double Kp, double Ki, double Kd)
    : setpoint(0), input(0), output(0), Kp(Kp), Ki(Ki), Kd(Kd), pid(&input, &output, &setpoint, Kp, Ki, Kd, PID::DIRECT) {}

void PIDController::begin()
{
    pid.SetMode(PID::AUTOMATIC);
}

void PIDController::setSetpoint(double sp)
{
    setpoint = sp;
}

void PIDController::setInput(double in)
{
    input = in;
}

double PIDController::compute()
{
    pid.Compute();
    return output;
}

double PIDController::getOutput()
{
    return output;
}
