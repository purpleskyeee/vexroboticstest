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
  bool intake=Controller.ButtonR2.pressing(); // Check if the intake button is pressed
  bool outtake=Controller.ButtonR1.pressing(); // Check if the outtake button is pressed

  bool rubberbandtoggle=Controller.ButtonY.pressing(); // Check if the rubberband toggle button is pressed
  bool middescoretoggle=Controller.ButtonA.pressing(); // Check if the middescore toggle button is pressed
  bool parking=Controller.ButtonX.pressing(); // Check if the parking button is pressed
  bool tonguemechtoggle=Controller.ButtonB.pressing(); // Check if the tonguemech toggle button is pressed
  bool hoodtoggle=Controller.ButtonL2.pressing(); // Check if the hood toggle button is
  

  std::cout<<"Axis Up: " << axis3 << ", Axis Left: " << axis1 << std::endl; // Print axis values for debugging
  // Use the controller axis values to control the motors
  bot.movecntrl(leftmotors,Left_Power); // Move left motor 
  bot.movecntrl(rightmotors,Right_Power); // Move right motor
/*
  if(tonguemechtoggle && !tonguemechdown)
  {
    tonguemech.open(); //put down tonguemech
    tonguemechdown=true;
  }
  else if(tonguemechtoggle && tonguemechdown)
  {
    tonguemech.close(); //put up tonguemech
    tonguemechdown=false;
  }

  if(parking && !parked)
  {
    park.open(); //put down parking mech
    parked=true;
  }
  else if(parking && parked)
  {
    park.close(); //put up parking mech
    parked=false;
  }

  if(rubberbandtoggle && !rubberbandon) //open and close aren't tested for the next three
  {
    rubberband.open(); //activate rubberband mech
    rubberbandon=true;
  }
  else if(rubberbandtoggle && rubberbandon)
  {
    rubberband.close(); //deactivate rubberband mech
    rubberbandon=false;
  }

  if(middescoretoggle && !middescoreon)
  {
    middescore.open(); //activate middescore mech
    middescoreon=true;
  }
  else if(middescoretoggle && middescoreon)
  {
    middescore.close(); //deactivate middescore mech
    middescoreon=false;
  }
*/
  if(hoodtoggle)
  {
    hoodMotor.spin(vex::directionType::fwd, 12800, vex::voltageUnits::mV); // Start hood motor at 128
  }
  else 
  {
    hoodMotor.stop(); // Stop hood motor
  }
    

  if(intake)
  {
    std::cout<<"intake"<<std::endl;
    intakeMotor.setReversed(false);
    intakeMotor.spin(vex::directionType::fwd, 12800, vex::voltageUnits::mV); // Start intake motors at 128
  }

  else if(outtake)
  {
    std::cout<<"outntake"<<std::endl;
    intakeMotor.spin(vex::directionType::rev, 12800, vex::voltageUnits::mV); // Start outtake motors at -128
  }

  else 
  {
    intakeMotor.stop(); // Stop intake motors
  }

  std::cout<<"Intake Button: " << intake << ", Outtake Button: " << outtake << std::endl; // Print button states for debugging
  std::cout<<"hood: " << hoodtoggle << std::endl;
}

void awpautonrightred()
{
  tonguemech.close(); //put down tonguemech
  pidForward(24); //forward 1 tile
  pidTurn(-90); //face loader
  intakeMotor.spinFor(2,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)

  pidForward(-24); //back 1 tile so aligner hits long goal
  tonguemech.open();//put up tonguemech
  intakeMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
  hoodMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time

  pidTurn(-90); //turn to the dihhs
  intakeMotor.spin(vex::directionType::fwd,128,vex::voltageUnits::mV); //start intake
  pidForward(72); //collect all
  intakeMotor.spin(vex::directionType::fwd,0,vex::voltageUnits::mV); //start intake

  pidTurn(45); //butt face mid goal
  intakeMotor.spinFor(2,vex::timeUnits::sec); //outtake mid for 3 ball time //TEMPPPPP
  hoodMotor.spinFor(2,vex::timeUnits::sec); //outtake mid for 3 ball time

  tonguemech.close();//tonguemech down
  pidForward(72); //go to 2nd loader
  intakeMotor.spinFor(2,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)

  pidForward(-24); //to 2nd long goal
  tonguemech.open();//put up tonguemech
  intakeMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
  hoodMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
}

int main() 
{
  // Prevent main from exiting with an infinite loop.
  Odom.ResetPosition();
  while (true)
  {
    //Odom.Calculate(); 
    drivewhee(); // Call the drive function to control the robot
    //std::cout<<"X: " << Odom.GetX() << ", Y: " << Odom.GetY() << ", Angle: " << Odom.GetAngle() << std::endl; // Print odometry values for debugging
    wait(5, msec);
  }

}
