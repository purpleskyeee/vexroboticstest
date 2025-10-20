#include <vex.h>
#include "pathing.hpp"
#include "pid.hpp"
#include "bot.hpp"
#include "odom.hpp"
#include <iostream>
#include <math.h>
#include <cmath>
using namespace vex;

void pathing::FollowPath(int a, int b, int c, int d, int lookahead, int tolerance) 
{
    /*
    FindPoint(a, b, c, d, lookahead); // Find the point on the path
    double turnangle=atan2((target_y - Odom.GetY()), (target_x - Odom.GetX())) * 180 / M_PI; // Calculate the angle to turn towards the target point in degrees
    if(turnangle < 0) turnangle += 360; // Normalize the angle to be between 0 and 360 degrees
    turnangle-= Odom.GetAngle(); // Adjust the angle based on the robot's current orientation
    if(turnangle < -180) turnangle += 360; // Normalize the angle to be between -180 and 180 degrees
    if(turnangle > 180) turnangle -= 360; // Normalize the angle to be between -180 and 180 degrees

    double distance = sqrt(pow(target_x - Odom.GetX(), 2) + pow(target_y - Odom.GetY(), 2));
    double linVelocity = VELOCITY_PROPORTION*distance; // Initialize linear velocity, velocity proportion needs to be adjusted
    double turnVelocity = bot.WIDTH * sin(turnangle * M_PI / 180) / lookahead * linVelocity; // Calculate turn velocity based on the angle and lookahead distance
    double leftVelocity = linVelocity - turnVelocity; // Calculate left motor velocity
    double rightVelocity = linVelocity + turnVelocity; // Calculate right motor velocity

    if(fabs(distance) <= tolerance) // If the robot is within the tolerance of the target point
    {
        leftVelocity = 0; // Stop left motor
        rightVelocity = 0; // Stop right motor
    }
    if(leftVelocity > bot.MAX_VELOCITY) leftVelocity = bot.MAX_VELOCITY; // Limit left motor velocity to maximum
    if(rightVelocity > bot.MAX_VELOCITY) rightVelocity = bot.MAX_VELOCITY; // Limit right motor velocity to maximum

    // Set the motor velocities
    bot.leftMotors[0].spin(vex::fwd, leftVelocity, vex::analogUnits::mV);
    bot.rightMotors[0].spin(vex::fwd, rightVelocity, vex::analogUnits::mV);
    */
}

void pathing::FindPoint(int a, int b, int c, int d, int lookahead) 
{
    /*
    // Calculate the point on the path using the cubic polynomial
    //pretend odometry gives you x,y relative to the robor pos in x,y;
    double pos_x = Odom.GetX(), pos_y = Odom.GetY(); // Replace with actual odometry values
    for(int x=pos_x-lookahead; x<pos_x+lookahead; x+0.1) // Iterate over a range of x values around the robot's position
    {
        int cube_y = a*pow(x,3) + b*pow(x,2) + c*x + d; // Calculate y using the cubic polynomial
        int circley=sqrt(lookahead-pow(x,2)+2*pos_x*x-pow(pos_x,2))+pos_y; // Calculate y using the circle equation
        // Check if the point is within tolerance
        if(cube_y == circley||cube_y==-circley)
        {
            //cout<<"Point found at x: " << x << ", y: " << cube_y << endl; // Print the found point for debugging
            target_x = x;
            target_y = cube_y;
        }
    }
    */
}