/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       niuniu                                                    */
/*    Created:      29/05/2025, 15:50:31                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "move_motor.hpp"
#include <iostream>
#include <vector>
using namespace vex;

//
// Main will set up the competition functions and callbacks.
//

controller Controller =controller();
int axisup=Controller.Axis2.position(), axislft=Controller.Axis4.position(); // Controller axis values
motor rm=motor(PORT1,vex::gearSetting::ratio18_1),lm=motor(PORT2,ratio6_1,true); // Right and Left motors
std::vector<motor> rightmotors = {rm}; // Vector to hold motors
std::vector<motor> leftmotors = {lm}; // Vector to hold motors
MoveMotor m;
int lasterror=0; // Variable to store last error for PID control

void drivewhee()
{
  axisup=Controller.Axis2.position();
  axislft=Controller.Axis4.position();
   std::cout<<"Axis Up: " << axisup << ", Axis Left: " << axislft << std::endl; // Print axis values for debugging
  // Use the controller axis values to control the motors

  m.manymovecntrl(leftmotors,axisup); // Move left motor 
  m.manymovecntrl(rightmotors,axisup); // Move right motor

  if(axislft>0){
    m.manymovecntrl(leftmotors,axislft); //Turn right motor forward
  }
  else if(axislft<0)
  {
    m.manymovecntrl(rightmotors,axislft); // Move left motor forward
  }
}

void pid(motor& m, int t,int kp,int kd)
{
  int pos = m.position(vex::degrees); // Get current motor position in degrees
  int error = t - pos; // Calculate the error between target and current position
  if(pos > t+2||pos<t-2) // Check if the motor position is less than target
  {
    lm.spin(fwd, kp*(t-pos)+kd*(error-lasterror), vex::voltageUnits::mV); // Spin left motor to 360 degrees with PID control
    lasterror = pos - t; // Calculate the error
  }
  else return;
}

int main() 
{
  // Prevent main from exiting with an infinite loop.
  lm.setPosition(0, vex::degrees); // Reset left motor position
  while (true) 
  {
    //drivewhee(); // Call the drive function to control the motors
    std::cout<< "Left Motor Position: " << lm.position(vex::degrees) << std::endl; // Print left motor position for debugging
    //it's 1080 cause gearbox makes it 3 times less than the real position
    lasterror=0;
    pid(lm,1080, 20, 10); // Call the PID function to control the left motor
    wait(5, msec);
  }
}
