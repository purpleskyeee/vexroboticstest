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
using namespace vex;

//
// Main will set up the competition functions and callbacks.
//

controller Controller =controller();
int axis=Controller.Axis2.position();
motor Motor1=motor(PORT1,ratio6_1);
MoveMotor m;

int main() {
  // Set up callbacks for autonomous and driver control periods

  // Prevent main from exiting with an infinite loop.
  while (true) {
    axis=Controller.Axis2.position();
    //Drivercontrol();
    wait(1000, msec);
  }
}
