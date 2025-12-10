#pragma once
#include "MovementRequest.h"

#define A1A 2
#define A1B 3
#define B1A 4
#define B1B 5

class MotorModule
{
public:
    void init();
    void execute(const MovementRequest& req);
private:
    
};