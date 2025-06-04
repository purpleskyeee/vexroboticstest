#ifndef MOVE_MOTOR_HPP
#define MOVE_MOTOR_HPP

#include <vex.h>
#include <vector>
using namespace vex;

class MoveMotor
{
public:
    void movecntrl(motor& m, int pct); //move motor by control
    void manymovecntrl(std::vector<motor>& motors, int pct); //move many motors by control
    //void movetime(motor&m, int t); //move motor by time
    void moveside(motor& a, motor& b, int pct); //move motor by side
};

#endif //MOVE_MOTOR_HPP