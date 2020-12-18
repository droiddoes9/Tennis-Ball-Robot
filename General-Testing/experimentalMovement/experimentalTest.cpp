#include "experimentalRobot.h"
#include "experimentalTurn.h"
#include "experimentalLine.h"

#define LEFT_MOTOR_DIR_PIN 0
#define LEFT_MOTOR_POWER_PIN 23
#define RIGHT_MOTOR_DIR_PIN 2
#define RIGHT_MOTOR_POWER_PIN 26

#define INITIAL_X 0
#define INITIAL_Y 0
#define INITIAL_THETA 0

#define L_ENCODER_PIN1 0
#define L_ENCODER_PIN2 7
#define R_ENCODER_PIN1 2
#define R_ENCODER_PIN2 3

int main()
{
    ExperimentalRobot r(LEFT_MOTOR_DIR_PIN, LEFT_MOTOR_POWER_PIN, RIGHT_MOTOR_DIR_PIN, RIGHT_MOTOR_POWER_PIN, INITIAL_X, INITIAL_Y, INITIAL_THETA, L_ENCODER_PIN1, L_ENCODER_PIN2, R_ENCODER_PIN1, R_ENCODER_PIN2);
    ExperimentalTurn turnRight(5, .1, 0, 0, 0);
    ExperimentalLine goStraight(10, .1, 0, 0, 0);
    r.addMovement(turnRight);
    r.addMovement(goStraight);
    r.run();
}