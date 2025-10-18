#include <vex.h>
#include "odom.hpp"
#include "pid.hpp"
#include "bot.hpp"
#include "definitions.hpp"
#include <iostream>
using namespace vex;

double odometry::encoder_to_inches(double encoder_counts) {
    return (encoder_counts / 360.0) * GEAR_RATIO * WHEEL_CIRCUMFERENCE;
}

double odometry::GetX() { return ODOMETRY_X; }

double odometry::GetY() { return ODOMETRY_Y; }

double odometry::GetAngle() { return ODOMETRY_ANGLE; }

void odometry::SetX(double x) { ODOMETRY_X = x; }

void odometry::SetY(double y) { ODOMETRY_Y = y; }

void odometry::SetAngle(double angle) { ODOMETRY_ANGLE = angle; }


void odometry::Calculate()
{
    double delta_x = encoder_to_inches(leftMotor.position(rotationUnits::deg) - last_left_pos);
    double delta_y = encoder_to_inches(rightMotor.position(rotationUnits::deg) - last_right_pos);
    double left_angle = leftMotor.position(rotationUnits::deg);
    double right_angle = rightMotor.position(rotationUnits::deg);

    double distance=(delta_x + delta_y) / 2.0;

    double raw_heading = Imu.heading(rotationUnits::deg);
    HEADING = raw_heading + initial_heading;
    HEADING = fmod(HEADING, 360.0); // Normalize heading to [0, 360)

    if(HEADING < 0)
    {
        HEADING += 360.0; // Ensure heading is positive
    }

    ODOMETRY_X += distance * sin(HEADING);
    ODOMETRY_Y += distance * cos(HEADING);


    last_left_pos = leftMotor.position(rotationUnits::deg);
    last_right_pos = rightMotor.position(rotationUnits::deg);
}

void odometry::ResetPosition()
{
    ODOMETRY_X = 0.0; // Reset x position
    ODOMETRY_Y = 0.0; // Reset y position
    HEADING = 0.0; // Reset angle
    last_left_pos = 0.0;
    last_right_pos = 0.0; // Reset last positions
    initial_heading = 0.0;
    Imu.setHeading(0, rotationUnits::deg); // Reset IMU heading
}
