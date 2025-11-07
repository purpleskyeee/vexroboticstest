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

//1,2,10,15,4,3

vex::motor lm1 = vex::motor(vex::PORT11, vex::gearSetting::ratio6_1, true); //11
vex::motor rm1 = vex::motor(vex::PORT12,  vex::gearSetting::ratio6_1, false);//12
vex::motor lm2 = vex::motor(vex::PORT13,  vex::gearSetting::ratio6_1, true);//13
vex::motor rm2 = vex::motor(vex::PORT14,  vex::gearSetting::ratio6_1, false);//14
vex::motor lm3 = vex::motor(vex::PORT15,  vex::gearSetting::ratio6_1, true);//15
vex::motor rm3 = vex::motor(vex::PORT16,  vex::gearSetting::ratio6_1, false);//16

std::vector<vex::motor> rightmotors = { rm1, rm2, rm3 };
std::vector<vex::motor> leftmotors  = { lm1, lm2, lm3 };

//12,11
vex::motor intakeMotor = vex::motor(vex::PORT10, vex::gearSetting::ratio6_1, false);//10
vex::motor hoodMotor = vex::motor(vex::PORT9, vex::gearSetting::ratio6_1, false);//9

pneumatics tonguemech(Brain.ThreeWirePort.B); 
bool tonguemechdown=false;
bool lasttonguepressstate=false;

pneumatics park(Brain.ThreeWirePort.E); //temp
bool parked=false;

pneumatics rubberband(Brain.ThreeWirePort.C); 
bool rubberbandon=true;
bool lastbandpressstate=true;

pneumatics middescore(Brain.ThreeWirePort.G); //temp
bool middescoreon=false;

bool lastdefensestate=false;
int defensechange=1;

vex::inertial Imu = vex::inertial(vex::PORT1);
vex::rotation FRONTRotation = vex::rotation(vex::PORT5);
vex::rotation BACKRotation  = vex::rotation(vex::PORT4);

const double WHEEL_CIRCUMFERENCE = 3.75 * M_PI;
const double GEAR_RATIO = 48.0 / 36.0;
const double MAX_VELOCITY = 128.0;
const double OFFSETL = 0.5;
const double OFFSETB = 16.0;
double HEADING = 0.0;
