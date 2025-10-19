#ifndef ODOM_HPP
#define ODOM_HPP
#include <vex.h>
#include "pid.hpp"
#include "bot.hpp"
#include "definitions.hpp"
#include <iostream>
using namespace vex;

class odometry {
public:
    double ODOMETRY_X = 0.0; // Current x position of the robot (global)
    double ODOMETRY_Y = 0.0; // Current y position of the robot (global)
    double ODOMETRY_ANGLE = 0.0; // Current angle of the robot in degrees (global)
    double initial_heading = 0.0;
    double last_front_pos = 0.0;
    double last_back_pos = 0.0;

    double odometry::encoder_to_inches(double encoder_counts) {}

    double GetX() {}

    double GetY() {}
    
    double GetAngle() {}

    void SetX(double x) {}

    void SetY(double y) {}
    
    void SetAngle(double angle) {}

    void ConstrainAngle(double& angle) {}

    void Calculate() {}

    void ResetPosition() {}
};
#endif //ODOM_HPP