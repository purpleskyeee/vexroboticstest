#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include "vex.h"
#include "pid.hpp"
#include "bot.hpp"
#include "odom.hpp"

extern vex::controller Controller;
extern vex::brain Brain;
extern Bot bot;
extern double axis3, axis1; // Controller axis values
extern PID pid_forward; //TODO: FILL IN WITH CONSTRUCTOR VALUES
extern PID pid_turn; //TODO: FILL IN WITH CONSTRUCTOR VALUES
extern odometry Odom;

extern double Left_Power;
extern double Right_Power;

controller Controller =controller();
Bot bot;
double axis3=Controller.Axis3.position(), axis1=Controller.Axis1.position(); // Controller axis values

motor lm1=motor(PORT10,vex::gearSetting::ratio6_1,1),
rm1=motor(PORT1,vex::gearSetting::ratio6_1,0),
lm2=motor(PORT9,vex::gearSetting::ratio6_1,1),
rm2=motor(PORT2,vex::gearSetting::ratio6_1,0),
lm3=motor(PORT8,vex::gearSetting::ratio6_1,1),
rm3=motor(PORT3,vex::gearSetting::ratio6_1,0); // Right and Left motors

std::vector<motor> rightmotors = {rm1, rm2, rm3}; // Vector to hold motors
std::vector<motor> leftmotors = {lm1, lm2, lm3}; // Vector to hold motors

//optical DistanceSensor = optical(PORT7); // Optical sensor for distance detection
//optical ColorSensor = optical(PORT5); // Optical sensor for color detection

extern inertial Imu; // Initialize the IMU on PORT1
extern motor leftMotor; // Initialize the left motor on PORT2
extern motor rightMotor; // Initialize the right motor on PORT3

extern const double WHEEL_CIRCUMFERENCE = 3.75*M_PI; // Wheel circumference in inches
extern const double GEAR_RATIO = 48/36; // Gear ratio
extern const double MAX_VELOCITY = 128; // Maximum velocity in mV
extern const double OFFSETL = ; // Left/front offset of the tracking wheel from center in inches
extern const double OFFSETB = ; // Right/back offset of the tracking wheel from center in inches
extern double HEADING; //heading
    
extern vex::rotation FRONTRotation(PORT5);
extern vex::rotation BACKRotation(PORT4);

#endif // DEFINITIONS_HPP