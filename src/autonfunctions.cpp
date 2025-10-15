#include "definitions.hpp"
#include "pathing.hpp"
#include "odom.hpp"
#include "pid.hpp"
#include "bot.hpp"

void pidForward(double target)
{
    double startleft=Odom.encoder_to_inches(leftmotors[0].position(deg));
    double startright=Odom.encoder_to_inches(rightmotors[0].position(deg));

    double currentleft=0;
    double currentright=0;
    while(!pid_forward.Arrived())
    {
        Odom.Calculate();
        currentleft=Odom.encoder_to_inches(leftmotors[0].position(deg));
        currentright=Odom.encoder_to_inches(rightmotors[0].position(deg));


        double currtrav=((currentleft-startleft)+(currentright-startright))/2.0;
        double power=pid_forward.calculatepower(currtrav);
        Right_Power=power;
        Left_Power=power;

    }
}