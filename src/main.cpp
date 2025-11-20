#include "vex.h"
#include "bot.hpp"
#include "pid.hpp"
#include "definitions.hpp"
#include "autonfunctions.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace vex;

competition Competition;

void drivewhee()
{
  //while(true)
  //{
    axis3=Controller.Axis3.position();
    axis1=Controller.Axis1.position();
    Right_Power=axis3-defensechange*axis1;
    Left_Power=axis3+defensechange*axis1;
    if(Right_Power>128) Right_Power=128;
    if(Right_Power<-128) Right_Power=-128;
    if(Left_Power>128) Left_Power=128;
    if(Left_Power<-128) Left_Power=-128;
    bool intakebutnoscore=Controller.ButtonR1.pressing(); // Check if the intake button is pressed
    bool score=Controller.ButtonR2.pressing(); // Check if the outtake button is pressed
    bool tonguemechtoggle=Controller.ButtonL2.pressing(); // tongue
    bool outtake=Controller.ButtonL1.pressing();

    bool rubberbandtoggle=Controller.ButtonY.pressing(); // Check if the rubberband toggle button is pressed
    bool middescoretoggle=Controller.ButtonRight.pressing(); // Check if the middescore toggle button is pressed'
    bool sidedescoretoggle=Controller.ButtonDown.pressing();
    //bool parking=Controller.ButtonX.pressing(); // Check if the parking button is pressed
    bool defensing=Controller.ButtonA.pressing();


    
    
    

    //std::cout<<"Axis Up: " << axis3 << ", Axis Left: " << axis1 << std::endl; // Print axis values for debugging
    // Use the controller axis values to control the motors
    bot.movecntrl(leftmotors,defensechange*Left_Power); // Move left motor 
    bot.movecntrl(rightmotors,defensechange*Right_Power); // Move right motor
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
    /*
    if(tonguemechtoggle!=lasttonguepressstate)
    {
      if(tonguemechdown) tonguemechdown=false; //false for tongue
      else tonguemechdown=true; //true for tongue
    }
    */

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

    if(middescoretoggle!=lastdescorepressstate)
    {
      if(middescoreon) middescoreon=false;
      else middescoreon=true;
    }

    if(sidedescoretoggle!=lastsiddescorestate)
    {
      if(descoreup) descoreup=false;
      else descoreup=true;
    }

    if(defensing!=lastdefensestate)
    {
      defensechange*=-1;
    }

    lasttonguepressstate=tonguemechtoggle;
    if(tonguemechdown) tonguemech.close(); 
    else tonguemech.open();

    lastbandpressstate=rubberbandtoggle;
    if(rubberbandon) rubberband.close();
    else rubberband.open();

    lastdescorepressstate=middescoretoggle;
    if(middescoreon) middescore.open();
    else middescore.close();

    lastsiddescorestate=sidedescoretoggle;
    if(descoreup) sidedescore.open();
    else sidedescore.close();

    printf("%d", middescoreon);

    //wait(20,vex::timeUnits::msec);
  //}
}

void auton(void)
{
  tonguemech.close();
  bot.movecntrl(leftmotors,-12800);
  bot.movecntrl(rightmotors,-12800);
  wait(800,msec);
  bot.movecntrl(leftmotors,0);
  bot.movecntrl(rightmotors,0);
}


int main() 
{
  // Prevent main from exiting with an infinite loop.
  Imu.calibrate(); //pause for 3 seconds
  while(Imu.isCalibrating())
  {
    wait(100, msec);
  }
  std::cout<<"Imu Calibrated"<<std::endl;
  bot.Reset();

  //auton();

  //Competition.autonomous(auton);
  //Competition.drivercontrol(drivewhee);

  //pidTurn(180);

  
  while (true)
  {
    Odom.CalculateWithoutTracking(); 
    drivewhee(); // Call the drive function to control the robot
    printf("imu angle = %f\n", Imu.heading(vex::rotationUnits::deg));
    printf("X: %.2f, Y: %.2f, Angle: %.2f\n", Odom.GetX(), Odom.GetY(), Odom.GetAngle());
    wait(20, msec); // Small delay to prevent wasted resources
  }
  

}
