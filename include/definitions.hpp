#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include "vex.h"
#include "pid.hpp"
#include "bot.hpp"
#include "odom.hpp"
#include <vector>

using namespace vex;

extern vex::controller Controller;
extern vex::brain Brain;
extern Bot bot;
extern double axis3;
extern double axis1;

extern PID pid_forward;
extern PID pid_turn;

extern odometry Odom;

extern double Left_Power;
extern double Right_Power;

extern vex::motor lm1;
extern vex::motor rm1;
extern vex::motor lm2;
extern vex::motor rm2;
extern vex::motor lm3;
extern vex::motor rm3;

extern std::vector<vex::motor> rightmotors;
extern std::vector<vex::motor> leftmotors;

extern vex::motor intakeMotor;
extern vex::motor hoodMotor;

extern pneumatics tonguemech;
extern bool tonguemechdown;
extern bool lasttonguepressstate;

extern pneumatics park;
extern bool parked;

extern pneumatics rubberband;
extern bool rubberbandon;
extern bool lastbandpressstate;

extern pneumatics middescore;
extern bool lastdescorepressstate;
extern bool middescoreon;

extern pneumatics hood;
extern bool lasthoodpressstate;
extern bool hoodup;

extern bool defense;
extern bool lastdefensestate;
extern int defensechange;

extern vex::inertial Imu;
extern vex::rotation FRONTRotation;
extern vex::rotation BACKRotation;

extern const double WHEEL_CIRCUMFERENCE;
extern const double GEAR_RATIO;
extern const double MAX_VELOCITY;
extern const double OFFSETL;
extern const double OFFSETB;
extern double HEADING;

#endif // DEFINITIONS_HPP