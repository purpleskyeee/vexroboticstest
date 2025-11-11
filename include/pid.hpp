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
    PID(double kp, double ki, double kd, double error_range, double gamma)
        : kp(kp), ki(ki), kd(kd), error_range(error_range), last_error(0), integral(0), gamma(gamma), leastpower(10), maxpower(50), target(0), arrived(false) {}

    void reset();
    
    void SetTarget(double t);

    bool Arrived();

    double calculatepower(double target);
};
#endif //PID_HPP