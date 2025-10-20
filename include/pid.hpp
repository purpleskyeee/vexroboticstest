#ifndef PID_HPP
#define PID_HPP
#include <vex.h>
#include <iostream>

class PID
{
public:
    double kp,kd,ki;
    double error_range;
    double last_error;
    double integral;
    double gamma;
    double leastpower;
    double maxpower;
    double target;

    bool arrived;
    //constructor
    PID(double kp, double kd, double ki, double error_range, double gamma)
        : kp(kp), kd(kd), ki(ki), error_range(error_range), last_error(0), integral(0), gamma(gamma), leastpower(0), maxpower(100), target(0), arrived(false) {}

    void reset();
    
    void SetTarget(double t);

    bool Arrived();

    double calculatepower(double target);
};
#endif //PID_HPP