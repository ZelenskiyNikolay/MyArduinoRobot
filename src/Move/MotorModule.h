#pragma once
#include "MovementRequest.h"

#define A1A 4
#define A1B 5
#define B1A 6
#define B1B 7
#define SPEED 150
#define MAX_CORR 30

class MotorModule
{
public:
    void init();
    void forward();
    void backward();
    void left();
    void right();
    void stop();
    void execute(const MovementRequest &req);
    void setCorrectionLeft(int v);
    void setCorrectionRight(int v);
    void ResetCorrection();

    void CorectionSpeed(int Left, int Right);

    void forward(int Left, int Right);
    void backward(int Left, int Right);

    void stopLeft();
    void stopRight();

    void forwardLeft();
    void forwardRight();
    void backwardRight();
    void backwardLeft();

    int corrLeft = 45;
    int corrRight = 0;
private:
    

};