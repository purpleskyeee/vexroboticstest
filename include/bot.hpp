#ifndef BOT_HPP
#define BOT_HPP
#include <vex.h>
#include <vector>

class Bot
{
public:
    double WIDTH; //width in inches
    double MAX_VELOCITY; //maximum velocity in mV
    std::vector<vex::motor> leftMotors;
    std::vector<vex::motor> rightMotors;
    void movecntrl(std::vector<vex::motor>& motors, int pct);
    void Reset();
};

#endif // BOT_HPP