#include "odometry.h"
#include "../math/vector.h"
#include "../math/mathUtil.h"
#include <cmath>
#include <iostream>
#include <cstdlib>

#define TRACKWIDTH 9.98330666439
#define PULSES_PER_REV 1440.0
#define LEFT_WHEEL__DIAMETER 2.505
#define RIGHT_WHEEL_DIAMETER 2.4955

//defenitions, just like we define functions below
double globalXPos = 0;
double globalYPos = 0;
double globalHeading = 0; //in degrees, from -180 to 180, 0 is forwards, positive angle to the left

double prevLeft = 0;
double prevRight = 0;
double leftChange = 0;
double rightChange = 0;

void setPose(double x, double y, double theta)
{
    globalXPos = x;
    globalYPos = y;
    globalHeading = theta;
}

void updateLeftEncoder(double reading)
{
    const double currentPulses = reading; //actual encoder reading
    const double currentRotations = currentPulses / PULSES_PER_REV;
    const double currentInches = currentRotations * LEFT_WHEEL__DIAMETER * M_PI;
    leftChange = currentInches - prevLeft;
    prevLeft = currentInches;
}

void updateRightEncoder(double reading)
{
    const double currentPulses = reading; //actual encoder reading
    const double currentRotations = currentPulses / PULSES_PER_REV;
    const double currentInches = currentRotations * RIGHT_WHEEL_DIAMETER * M_PI;
    rightChange = currentInches - prevRight;
    prevRight = currentInches;
}

void updatePos(double leftReading, double rightReading)
{
    //find left and right change
    updateLeftEncoder(leftReading);
    updateRightEncoder(rightReading);

    //store initialHeading for later
    const double initialHeading = globalHeading;
    const double initialHeadingRad = toRadians(initialHeading);

    const double angleChangeRad = (leftChange - rightChange) / TRACKWIDTH;
    const double angleChangeDeg = toDegrees(angleChangeRad);
    globalHeading = angleWrapDeg(globalHeading + angleChangeDeg);

    const double movement = (leftChange + rightChange) / 2.0; // total change in movement by robot (dx)
    const double dTheta = angleChangeRad;

    const double sinTheta = sin(dTheta);
    const double cosTheta = cos(dTheta);

    double sineTerm;
    double cosTerm;

    //if we have almost no angle change
    if (epsilonEquals(dTheta, 0))
    {
        sineTerm = 1.0 - 1.0 / 6.0 * dTheta * dTheta;
        cosTerm = dTheta / 2.0;
    }
    else //we have angle change
    {
        sineTerm = sinTheta / dTheta;
        cosTerm = (1 - cosTheta) / dTheta;
    }

    Vector deltaVector = Vector(sineTerm * movement, cosTerm * movement); //translation
    deltaVector = deltaVector.rotated(initialHeadingRad);

    //switch x, y because thats then +y is forward
    //have to do testing to figure out signs and which is which
    globalXPos += deltaVector.getY();
    globalYPos -= deltaVector.getX();
}

double getX() {return globalXPos;}
double getY() {return globalYPos;}
double getHeading() {return globalHeading;}