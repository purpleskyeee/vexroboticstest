#include "vex.h"
#include "move_motor.hpp"
#include <vector>

void MoveMotor::movecntrl(motor& m,int pct)
{
    m.spin(fwd,128 * pct,vex::voltageUnits::mV);
}

void MoveMotor::manymovecntrl(std::vector<motor>& motors, int pct)
{
    for(auto& m : motors) {
        m.spin(fwd,128 * pct,vex::voltageUnits::mV);
    }
}

void MoveMotor::moveside(motor& a, motor& b, int pct)
{
    a.spin(fwd,128 * pct,vex::voltageUnits::mV);
    b.spin(fwd,128 * pct,vex::voltageUnits::mV);
}