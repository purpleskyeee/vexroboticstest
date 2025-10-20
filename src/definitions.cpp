#include "vex.h"
#include "definitions.hpp"

// VEX hardware objects
vex::controller Controller = vex::controller();
vex::brain Brain = vex::brain();

// Bot / PID / Odometry instances
Bot bot;
PID pid_forward(66.0, 66.0, 66.0, 50.0, 0.9);
PID pid_turn(66.0, 66.0, 66.0, 50.0, 0.9);
odometry Odom(0.0,0.0,0.0); // Initialize odometry at (0,0) with 0 angle

// Controller axes (keep initialized at 0; update at runtime)
double axis3 = 0;
double axis1 = 0;

double Left_Power = 0;
double Right_Power = 0;

// Motors (use vex::PORTx)
vex::motor lm1 = vex::motor(vex::PORT10, vex::gearSetting::ratio6_1, true);
vex::motor rm1 = vex::motor(vex::PORT1,  vex::gearSetting::ratio6_1, false);
vex::motor lm2 = vex::motor(vex::PORT9,  vex::gearSetting::ratio6_1, true);
vex::motor rm2 = vex::motor(vex::PORT2,  vex::gearSetting::ratio6_1, false);
vex::motor lm3 = vex::motor(vex::PORT8,  vex::gearSetting::ratio6_1, true);
vex::motor rm3 = vex::motor(vex::PORT3,  vex::gearSetting::ratio6_1, false);

std::vector<vex::motor> rightmotors = { rm1, rm2, rm3 };
std::vector<vex::motor> leftmotors  = { lm1, lm2, lm3 };

vex::inertial Imu = vex::inertial(vex::PORT1);
vex::rotation FRONTRotation = vex::rotation(vex::PORT5);
vex::rotation BACKRotation  = vex::rotation(vex::PORT4);

const double WHEEL_CIRCUMFERENCE = 3.75 * M_PI;
const double GEAR_RATIO = 48.0 / 36.0;
const double MAX_VELOCITY = 128.0;
const double OFFSETL = 0.5;
const double OFFSETB = 16.0;
double HEADING = 0.0;
