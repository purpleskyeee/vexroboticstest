#ifndef PATHING_HPP
#define PATHING_HPP

#include "vex.h"
#include "pid.hpp"
#include "bot.hpp"
#include <iostream>
using namespace vex;

class pathing {
public:
    int a,b,c,d; //ax^3+bx^2+cx+d
    int lookahead = 100; // Distance to look ahead in mm
    int tolerance; // Tolerance in mm for following the path, changed by function
    int target_x, target_y; // Target coordinates to follow the path
    void FollowPath(int a, int b, int c, int d, int lookahead, int tolerance);
    void FindPoint(int a, int b, int c, int d, int lookahead);
};

#endif // PATHING_HPP