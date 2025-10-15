#include <vex.h>
#include "odom.hpp"
#include "pid.hpp"
#include "bot.hpp"
#include <iostream>
using namespace vex;
/*
double odometry::encoder_to_inches(double encoder_counts) {
    return (encoder_counts / 360.0) * GEAR_RATIO * WHEEL_CIRCUMFERENCE; //temporary
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

    double distance=(delta_x + delta_y) / 2.0;

    double raw_heading = Imu.heading(rotationUnits::deg);
    ODOMETRY_ANGLE = raw_heading * (M_PI/180.0) + initial_heading;
    ODOMETRY_ANGLE = fmod(ODOMETRY_ANGLE, 2 * M_PI); // Normalize heading to [0, 2π)

    if(ODOMETRY_ANGLE < 0)
    {
        ODOMETRY_ANGLE += 2 * M_PI; // Ensure heading is positive
    }

    ODOMETRY_X += distance * sin(ODOMETRY_ANGLE);
    ODOMETRY_Y += distance * cos(ODOMETRY_ANGLE);

    last_left_pos = leftMotor.position(rotationUnits::deg);
    last_right_pos = rightMotor.position(rotationUnits::deg);
}

/*
void odometry::CalculatePositionAngle()
{
    double left_angle = leftMotor.position(rotationUnits::deg);
    double right_angle = rightMotor.position(rotationUnits::deg);
    ODOMETRY_ANGLE += (left_angle - right_angle) / 2.0; // Average the angles of both motors
    ODOMETRY_ANGLE = fmod(ODOMETRY_ANGLE, 360.0); // Normalize angle to [0, 360)
}


void odometry::ResetPosition()
{
    ODOMETRY_X = 0.0; // Reset x position
    ODOMETRY_Y = 0.0; // Reset y position
    ODOMETRY_ANGLE = 0.0; // Reset angle
    last_left_pos = 0.0;
    last_right_pos = 0.0; // Reset last positions
    initial_heading = 0.0;
    Imu.setHeading(0, rotationUnits::deg); // Reset IMU heading
}
*/