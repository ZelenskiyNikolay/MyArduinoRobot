#pragma once
#include "MotorModule.h"
#include "MovementRequest.h"

class SafetyModule {
private:
    MotorModule motor;

    MovementRequest current;
    unsigned long elapsed = 0;
    bool active = false;

public:
    SafetyModule(MotorModule& motor);

    void process(const MovementRequest& req);

    void startRequest(const MovementRequest& req);
    bool update(unsigned long dt); 
    bool isBusy() const;
};