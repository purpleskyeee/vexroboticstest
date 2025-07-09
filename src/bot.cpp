#include <vector>
#include "vex.h"
#include "bot.hpp"

void Bot::movecntrl(std::vector<vex::motor>& motors, int pct) {
    for (auto& motor : motors) {
        motor.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
    }
}