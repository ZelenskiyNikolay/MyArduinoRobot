#pragma once
#include "MotorModule.h"
#include "MovementRequest.h"
#include "Sensors/SurfaceSensor.h"

enum SafetyTriger{
    NONE,
    SENSOR_LEFT,
    SENSOR_RIGHT,
    MENY_SENSORS
};

class SafetyModule {
private:
    MotorModule motor;

    MovementRequest current;
    unsigned long elapsed = 0;
    bool active = false;
    bool Ready = false;
    SurfaceSensor sensorLeft,sensorRight;
    SafetyTriger triger;
public:
    SafetyModule(MotorModule& motor);

    void process(const MovementRequest& req);

    void startRequest(const MovementRequest& req);
    int update(float dt); 
    bool isBusy() const;
};