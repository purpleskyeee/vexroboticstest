#ifndef ODOM_HPP
#define ODOM_HPP
#include <vex.h>
#include "pid.hpp"
#include "bot.hpp"
#include <iostream>
using namespace vex;

extern inertial Imu; // Initialize the IMU on PORT1
extern motor leftMotor; // Initialize the left motor on PORT2
extern motor rightMotor; // Initialize the right motor on PORT3

class odometry {
public:
    double ODOMETRY_X = 0.0; // Current x position of the robot
    double ODOMETRY_Y = 0.0; // Current y position of the robot
    double ODOMETRY_ANGLE = 0.0; // Current angle of the robot in degrees
    double initial_heading = 0.0;
    double last_left_pos = 0.0;
    double last_right_pos = 0.0;

    double odometry::encoder_to_inches(double encoder_counts) {}

    double GetX() {}

    double GetY() {}
    
    double GetAngle() {}

    void SetX(double x) {}

    void SetY(double y) {}
    
    void SetAngle(double angle) {}

    void Calculate()
    {}

    void ResetPosition() 
    {}
};
#endif //ODOM_HPP