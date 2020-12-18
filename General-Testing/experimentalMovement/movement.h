#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../motor/motorPowers.h"
#include "../math/pose.h"
#include <ctime>
class Movement
{
    protected:
    double leftPower;
    double rightPower;

    double kp;
    double ki;
    double kd;
    double f;

    std::clock_t timer;
    double pastTime;
    double currentTime;

    double error;
    double pastError;

    double integral;

    bool done;

    public:
    motorPowers getPowers();
    bool finished();
    
    virtual void updatePower(pose currentPose);

    virtual void beginMovement(pose startPose);

    virtual ~Movement(){};
};
#endif