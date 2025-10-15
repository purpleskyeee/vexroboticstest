#include <vector>
#include <iostream>
#include "vex.h"
#include "bot.hpp"

void Bot::movecntrl(std::vector<vex::motor>& motors, int pct) {
    std::cout<<"Moving motors at " << pct << " percent" << std::endl; // Debugging output
    for (auto& motor : motors) {
        std::cout<<"poop"<<std::endl;
        motor.spin(vex::directionType::fwd, 128*pct, vex::voltageUnits::mV);
    }
}