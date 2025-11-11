#include "vex.h"
#include "pid.hpp"
#include "bot.hpp"
#include <iostream>
using namespace vex;

void PID::reset()
{
  kp=0; kd=0; ki=0; 
  error_range=0; 
  last_error=0; 
  integral=0; 
  gamma=0; 
  leastpower=10; 
  maxpower=50;
  target=0;
  arrived=false;
}

void PID::SetTarget(double t) { target=t; }

bool PID::Arrived(){return arrived;}

double PID::calculatepower(double currpos)
{
  double error = target - currpos; // Calculate the error between target and current position
  double power= kp * error + kd * (error - last_error) + ki * integral; // Calculate power using PID formula
  if(power > maxpower) power = maxpower; // Limit power to maximum value
  if(power < leastpower) power = leastpower; // Limit power to minimum value

  printf("out %f %f\n",fabs(error),error_range);
  if (fabs(error) <= error_range) // Check if the motor position is less than target
  {
    printf("in %f %f\n",fabs(error),error_range);
    arrived = true;
    power=0;
  }
  else
  {
    last_error = error; // Update error
    integral=(integral+last_error)*gamma; //calculate the integral with adjustments to keep integral value low
  }
  return power;
}




/*
hongkou reference
void pidForward(double target)
{
 
   while (error > errorTolerance || speed > speedTolerance)
   {
    error = target - (m.position(deg) - startpos);
    speed = -m.velocity(dps)/100;
    if (fabs(error) < 50)
    {
      integral += error;
    }
    else integral = 0;

    if (error * lastError < 0)
    {
      integral = 0; 
    }
    output = error * Kp + integral * Ki + speed * Kd;
    drive(output);
    lastError = error;
    vexDelay(10);
   }
   drive(0);
}
*/