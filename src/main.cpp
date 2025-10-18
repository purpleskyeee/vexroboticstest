#include "vex.h"
#include "bot.hpp"
#include "pid.hpp"
#include "definitions.hpp"
#include <iostream>
#include <vector>
using namespace vex;

PID pid;

void drivewhee()
{
  axis3=Controller.Axis3.position();
  axis1=Controller.Axis1.position();
  int Right_Power=axis3-axis1;
  int Left_Power=axis3+axis1;
  if(Right_Power>128) Right_Power=128;
  if(Right_Power<-128) Right_Power=-128;
  if(Left_Power>128) Left_Power=128;
  if(Left_Power<-128) Left_Power=-128;
  //bool intake=Controller.ButtonR1.pressing(); // Check if the intake button is pressed
  //bool outtake=Controller.ButtonR2.pressing(); // Check if the outtake button is pressed
  //bool eat = Controller.ButtonL1.pressing(); // Check if the eat button is pressed
  

  std::cout<<"Axis Up: " << axis3 << ", Axis Left: " << axis1 << std::endl; // Print axis values for debugging
  // Use the controller axis values to control the motors
  bot.movecntrl(leftmotors,Left_Power); // Move left motor 
  bot.movecntrl(rightmotors,Right_Power); // Move right motor
/*
  if(intake)
  {
    bot.movecntrl(intakeMotors, 128); // Start intake motors at 128
  }

  if(outtake)
  {
    bot.movecntrl(intakeMotors, -128); // Start outtake motors at -128
  }
  
  if(eat)
  {
    
  }
  */
}


int main() 
{
  // Prevent main from exiting with an infinite loop.
  Odom.ResetPosition();
  while (true)
  {
    Odom.Calculate();
    drivewhee(); // Call the drive function to control the robot
    wait(5, msec);
  }

}
