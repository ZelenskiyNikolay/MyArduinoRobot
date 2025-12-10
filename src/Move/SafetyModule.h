#pragma once
#include "MotorModule.h"

class SafetyModule {
private:
    MotorModule& motor;

public:
    SafetyModule(MotorModule& m) : motor(m) {}

    void process(const MovementRequest& req);
};