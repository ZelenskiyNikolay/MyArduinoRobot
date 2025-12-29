#pragma once
#include "MovementRequest.h"

#define A1A 2
#define A1B 3
#define B1A 4
#define B1B 5
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
    void left(int Left, int Right);
    void right(int Left, int Right);
    
    int corrLeft = 0;
    int corrRight = 0;
private:
    

};