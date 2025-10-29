#ifndef ODOM_HPP
#define ODOM_HPP
#include <vex.h>
#include "pid.hpp"
#include "bot.hpp"
#include <iostream>
using namespace vex;

class odometry
{
public:
    double ODOMETRY_X; // Current x position of the robot (global)
    double ODOMETRY_Y; // Current y position of the robot (global)
    double ODOMETRY_ANGLE; // Current angle of the robot in degrees (global)
    double initial_heading;
    double last_front_pos; //in the case of no tracking wheels, this is left encoder avg
    double last_back_pos; //in the case of no tracking wheels, this is right encoder avg

    odometry(double x, double y, double angle)
        : ODOMETRY_X(x), ODOMETRY_Y(y), ODOMETRY_ANGLE(angle), initial_heading(0), last_front_pos(0), last_back_pos(0) {}

    double encoder_to_inches(double encoder_counts);

    double GetX();

    double GetY();
    
    double GetAngle();

    void SetX(double x);

    void SetY(double y);
    
    void SetAngle(double angle);

    void ConstrainAngle(double& angle);

    void CalculateWithTracking();

    void CalculateWithoutTracking();

    void ResetPosition();
};
#endif //ODOM_HPP