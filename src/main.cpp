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
  bool intakebutnoscore=Controller.ButtonR1.pressing(); // Check if the intake button is pressed
  bool score=Controller.ButtonR2.pressing(); // Check if the outtake button is pressed
  bool tonguemechtoggle=Controller.ButtonL2.pressing(); // Check if the hood toggle button is
  bool outtake=Controller.ButtonL1.pressing();

  bool rubberbandtoggle=Controller.ButtonY.pressing(); // Check if the rubberband toggle button is pressed
  bool middescoretoggle=Controller.ButtonA.pressing(); // Check if the middescore toggle button is pressed
  bool parking=Controller.ButtonX.pressing(); // Check if the parking button is pressed
  
  

  std::cout<<"Axis Up: " << axis3 << ", Axis Left: " << axis1 << std::endl; // Print axis values for debugging
  // Use the controller axis values to control the motors
  bot.movecntrl(leftmotors,Left_Power); // Move left motor 
  bot.movecntrl(rightmotors,Right_Power); // Move right motor
  if(intakebutnoscore)
  {
    hoodMotor.spin(vex::directionType::rev, bot.MAX_VELOCITY, vex::voltageUnits::mV); // Start hood motor at 128
    intakeMotor.spin(vex::directionType::fwd, bot.MAX_VELOCITY, vex::voltageUnits::mV); // Start intake motors at 128
  }
  else if(score)
  {
    hoodMotor.spin(vex::directionType::fwd, bot.MAX_VELOCITY, vex::voltageUnits::mV); // Start hood motor at 128
    intakeMotor.spin(vex::directionType::fwd, bot.MAX_VELOCITY, vex::voltageUnits::mV); // Start intake motors at 128
  }
  else if(outtake)
  {
    hoodMotor.spin(vex::directionType::rev, bot.MAX_VELOCITY, vex::voltageUnits::mV); // Start hood motor at 128
    intakeMotor.spin(vex::directionType::rev, bot.MAX_VELOCITY, vex::voltageUnits::mV); // Start intake motors at 128
  }
  else 
  {
    hoodMotor.stop(); // Stop hood motor
    intakeMotor.stop(); // Stop intake motors
  }
  
  if(tonguemechtoggle!=lasttonguepressstate)
  {
    if(tonguemechdown) tonguemechdown=false;
    else tonguemechdown=true;
  }

  if(rubberbandtoggle!=lastbandpressstate)
  {
    if(rubberbandon) rubberbandon=false;
    else rubberbandon=true;
  }

  lasttonguepressstate=tonguemechtoggle;
  if(tonguemechdown) tonguemech.close();
  else tonguemech.open();

  lastbandpressstate=rubberbandtoggle;
  if(rubberbandon) rubberband.open();
  else rubberband.close();
}

int main() 
{
  // Prevent main from exiting with an infinite loop.
  Imu.calibrate(); //pause for 3 seconds
  std::cout<<"Imu Calibrated"<<std::endl;
  bot.Reset();

  while (true)
  {
    Odom.CalculateWithoutTracking(); 
    drivewhee(); // Call the drive function to control the robot
    std::cout<<"X: " << Odom.GetX() << ", Y: " << Odom.GetY() << ", Angle: " << Odom.GetAngle() << std::endl; // Print odometry values for debugging
    wait(5, msec);
  }

}
