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

void odometry::ConstrainAngle(double& angle) 
{
    while (angle >= 2*M_PI) angle -= 2*M_PI;
    while (angle < 0.0) angle += 2*M_PI;
}


void odometry::CalculateWithTracking()
{
    double delta_l=encoder_to_inches(FRONTRotation.position(rotationUnits::deg)-last_front_pos); //from front tracking (currtracking wheel reading-last position)
    double delta_b=encoder_to_inches(BACKRotation.position(rotationUnits::deg)-last_back_pos); //from back tracking (currtracking wheel reading-last position)
    double delta_theta = Imu.heading(degrees)*M_PI/180.0+initial_heading;//from IMU (currheading-initial heading)-(last heading-initial heading)
    ConstrainAngle(delta_theta);

    double local_y=2*(delta_l/delta_theta+OFFSETL)*sin(delta_theta/2);
    double local_x=2*(delta_b/delta_theta+OFFSETB)*sin(delta_theta/2);

    double avg_theta=ODOMETRY_ANGLE+delta_theta/2;
    ODOMETRY_X+=local_x*cos(avg_theta)-local_y*sin(avg_theta);
    ODOMETRY_Y+=local_x*sin(avg_theta)+local_y*cos(avg_theta);
    ODOMETRY_ANGLE+=delta_theta;
    last_front_pos=FRONTRotation.position(rotationUnits::deg);
    last_back_pos=BACKRotation.position(rotationUnits::deg);
    ConstrainAngle(ODOMETRY_ANGLE);
}

void odometry::CalculateWithoutTracking()
{
    double left_pos=encoder_to_inches((lm1.position(rotationUnits::deg)+lm2.position(rotationUnits::deg)+lm3.position(rotationUnits::deg))/3.0);
    double right_pos=encoder_to_inches((rm1.position(rotationUnits::deg)+rm2.position(rotationUnits::deg)+rm3.position(rotationUnits::deg))/3.0);

    double delta_left=left_pos-last_front_pos;
    double delta_right=right_pos-last_back_pos;

    double curr_theta=Imu.heading(degrees)*M_PI/180.0-initial_heading;
    double delta_theta=curr_theta-ODOMETRY_ANGLE;
    ConstrainAngle(delta_theta);

    if(fabs(delta_theta)<1e-6)
    {
        double avg_distance = (delta_left + delta_right) / 2.0;
        ODOMETRY_X += avg_distance * cos(ODOMETRY_ANGLE);
        ODOMETRY_Y += avg_distance * sin(ODOMETRY_ANGLE);
    }
    else
    {
        double radius=(delta_right+delta_left)/(delta_theta*2.0);
        double delta_y=radius*(sin(ODOMETRY_ANGLE+delta_theta)-sin(ODOMETRY_ANGLE));
        double delta_x=-radius*(cos(ODOMETRY_ANGLE+delta_theta)-cos(ODOMETRY_ANGLE));

        ODOMETRY_X+=delta_x;
        ODOMETRY_Y+=delta_y;
        ODOMETRY_ANGLE = curr_theta;
        ConstrainAngle(ODOMETRY_ANGLE);
        // printf("odom angle = %f\n", ODOMETRY_ANGLE);
        // printf("DX: %.2f, DY: %f, DAngle: %f\n", delta_x, delta_y, delta_theta);
    }
    last_front_pos=left_pos;
    last_back_pos=right_pos;
}

void odometry::ResetPosition()
{
    ODOMETRY_X = 0.0; // Reset x position
    ODOMETRY_Y = 0.0; // Reset y position
    HEADING = 0.0; // Reset angle
    last_front_pos = 0.0;
    last_back_pos = 0.0; // Reset last positions
    initial_heading = 0.0;
    Imu.setHeading(0, rotationUnits::deg); // Reset IMU heading
}
