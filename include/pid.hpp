#ifndef PID_HPP
#define PID_HPP
#include <vex.h>
#include <iostream>

class PID
{
private:
    double kp,kd,ki;
    double error_range;
    double last_error;
    double integral;
    double gamma;
public:
    PID(double kp, double kd, double ki, double error_range, double gamma)
        : kp(kp), kd(kd), ki(ki), error_range(error_range), last_error(0), integral(0), gamma(1.0){}
    void pid(vex::motor& m, double t, double kp,double kd, double ki, double error_range, double gamma);
};
#endif //PID_HPP