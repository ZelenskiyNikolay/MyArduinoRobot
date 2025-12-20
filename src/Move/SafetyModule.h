#pragma once
#include "MotorModule.h"
#include "MovementRequest.h"
#include "Sensors/SurfaceSensor.h"
#include "Sensors/UltrasonicSensor.h"

enum SafetyTriger
{
    NONE,
    SENSOR_LEFT,
    SENSOR_RIGHT,
    SENSOR_BACK,
    SENSOR_BACK_FLOW,
    MENY_SENSORS
};

class SafetyModule
{
private:
    MotorModule motor;

    MovementRequest current;
    unsigned long elapsed = 0;
    bool active = false;
    bool Ready = false;
    SurfaceSensor sensorLeft, sensorRight;
    SurfaceSensor sensorBack, sensorBackFlow;
    SafetyTriger triger;

    UltrasonicModule ultrasonic; //(16,17);
public:
    static SafetyModule &getInstance()
    {
        static SafetyModule instance;
        return instance;
    }

    void process(const MovementRequest &req);

    void startRequest(const MovementRequest &req);
    int update(float dt);
    bool isBusy() const;
    void STOP_MOTORS();

private:
    SafetyModule();
    bool CheckSensors();
    SafetyTriger sensorTrigger = SafetyTriger::NONE;
    bool corection = false;
};