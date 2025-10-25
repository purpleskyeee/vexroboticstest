#include "definitions.hpp"
#include "odom.hpp"
#include "pid.hpp"

void pidForward(double target)
{
    double startleft=Odom.encoder_to_inches(leftmotors[0].position(deg));
    double startright=Odom.encoder_to_inches(rightmotors[0].position(deg));

    pid_forward.reset();
    pid_forward.SetTarget(target);

    double currentleft=0;
    double currentright=0;
    while(!pid_forward.Arrived())
    {
        currentleft=Odom.encoder_to_inches(leftmotors[0].position(deg));
        currentright=Odom.encoder_to_inches(rightmotors[0].position(deg));

        double currtrav=((currentleft-startleft)+(currentright-startright))/2.0;
        double power=pid_forward.calculatepower(currtrav);
        Right_Power=power;
        Left_Power=power;
    }
}

void turnconstrainangle(double& angle)
{
    while (angle > M_PI) angle -= 2*M_PI;
    while (angle < -M_PI) angle += 2*M_PI;
}

void pidTurn(double target)
{
    double startheading=Odom.GetAngle();
    target/=180*M_PI;
    turnconstrainangle(target);
    turnconstrainangle(startheading);
    double currentheading=0;

    pid_turn.reset();
    pid_turn.SetTarget(target);

    while(!pid_turn.Arrived())
    {
        currentheading=Odom.GetAngle();
        double currturn=currentheading-startheading;
        turnconstrainangle(currturn);

        double power=pid_turn.calculatepower(currturn);
        Right_Power=-power; //opposite power so it turns
        Left_Power=power;
    }
}