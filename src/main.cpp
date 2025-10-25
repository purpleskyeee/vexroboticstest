#include "vex.h"
#include "bot.hpp"
#include "pid.hpp"
#include "definitions.hpp"
#include "autonfunctions.hpp"
#include <iostream>
#include <vector>
using namespace vex;

void drivewhee()
{
  axis3=Controller.Axis3.position();
  axis1=Controller.Axis1.position();
  Right_Power=axis3-axis1;
  Left_Power=axis3+axis1;
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

void awpautonrightred()
{
  toungemech.close(); //put down toungemech
  pidForward(24); //forward 1 tile
  pidTurn(-90); //face loader
  intakeMotor1.spinFor(2,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)
  intakeMotor2.spinFor(2,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)

  pidForward(-24); //back 1 tile so aligner hits long goal
  toungemech.open();//put up toungemech
  intakeMotor1.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
  intakeMotor2.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time

  pidTurn(-90); //turn to the dihhs
  intakeMotor1.spin(vex::directionType::fwd,128,vex::voltageUnits::mV); //start intake
  intakeMotor2.spin(vex::directionType::fwd,128,vex::voltageUnits::mV); //start intake
  pidForward(72); //collect all
  intakeMotor1.spin(vex::directionType::fwd,0,vex::voltageUnits::mV); //start intake
  intakeMotor2.spin(vex::directionType::fwd,0,vex::voltageUnits::mV); //start intake

  pidTurn(45); //butt face mid goal
  intakeMotor1.setReversed(false);
  intakeMotor1.spinFor(2,vex::timeUnits::sec); //outtake mid for 3 ball time
  intakeMotor2.spinFor(2,vex::timeUnits::sec); //outtake mid for 3 ball time
  intakeMotor1.setReversed(true);

  toungemech.close();//toungemech down
  pidForward(72); //go to 2nd loader
  intakeMotor1.spinFor(2,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)
  intakeMotor2.spinFor(2,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)

  pidForward(-24); //to 2nd long goal
  toungemech.open();//put up toungemech
  intakeMotor1.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
  intakeMotor2.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
}

int main() 
{
  // Prevent main from exiting with an infinite loop.
  Odom.ResetPosition();
  while (true)
  {
    Odom.Calculate(); 
    drivewhee(); // Call the drive function to control the robot
    std::cout<<"X: " << Odom.GetX() << ", Y: " << Odom.GetY() << ", Angle: " << Odom.GetAngle() << std::endl; // Print odometry values for debugging
    wait(5, msec);
  }

}
