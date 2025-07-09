/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       niuniu                                                    */
/*    Created:      29/05/2025, 15:50:31                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "bot.hpp"
#include "pid.hpp"
#include <iostream>
#include <vector>
using namespace vex;

//
// Main will set up the competition functions and callbacks.
//

controller Controller =controller();
Bot bot;
int axisup=Controller.Axis2.position(), axislft=Controller.Axis4.position(); // Controller axis values
motor rm=motor(PORT1,vex::gearSetting::ratio18_1),lm=motor(PORT2,ratio6_1,true); // Right and Left motors
std::vector<motor> rightmotors = {rm}; // Vector to hold motors
std::vector<motor> leftmotors = {lm}; // Vector to hold motors
PID pid;
int lasterror=0; // Variable to store last error for PID control

void drivewhee()
{
  axisup=Controller.Axis2.position();
  axislft=Controller.Axis4.position();
   std::cout<<"Axis Up: " << axisup << ", Axis Left: " << axislft << std::endl; // Print axis values for debugging
  // Use the controller axis values to control the motors

  bot.movecntrl(leftmotors,axisup); // Move left motor 
  bot.movecntrl(rightmotors,axisup); // Move right motor

  if(axislft>0){
    bot.movecntrl(leftmotors,axislft); //Turn right motor forward
  }
  else if(axislft<0)
  {
    bot.movecntrl(rightmotors,axislft); // Move left motor forward
  }
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
    pid.pid(lm,1080, 20, 10, 0, 5); // Call the PID function to control the left motor
    wait(5, msec);
  }
}
