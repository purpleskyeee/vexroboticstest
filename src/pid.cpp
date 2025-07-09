#include "vex.h"
#include "pid.hpp"
#include "bot.hpp"
#include <iostream>

void PID::pid(vex::motor& m, double t, double kp,double kd, double ki, double error_range, double gamma)
{
  double pos = m.position(vex::degrees); // Get current motor position in degrees
  double error = t - pos; // Calculate the error between target and current position
  double power= kp * error + kd * (error - last_error) + ki * integral; // Calculate power using PID formula
  if(pos > t+error_range||pos<t-error_range) // Check if the motor position is less than target
  {
    m.spin(vex::fwd, power, vex::voltageUnits::mV); // Spin left motor to 360 degrees with PID control
    last_error = pos - t; // Calculate the error
    integral=(integral+last_error)*gamma; //calculate the integral with adjustments to keep integral value low
  }
  else return;
}

