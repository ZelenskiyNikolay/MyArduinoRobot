#pragma once
#include "MovementRequest.h"

#define A1A 2
#define A1B 3
#define B1A 4
#define B1B 5
#define SPEED 150

class MotorModule
{
public:
    void init();
    void forward();
    void backward();
    void left();
    void right();
    void stop();
    void execute(const MovementRequest& req);
};