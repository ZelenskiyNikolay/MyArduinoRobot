#pragma once
#include "MotorModule.h"
#include "MovementRequest.h"
#include "Sensors/SurfaceSensor.h"
#include "Sensors/UltrasonicSensor.h"
#include "Sensors/RPM_sensor.h"
#include "MotionController.h"
#include "SafetyModule.h"

#define ticks90Left 18
#define ticks90Right 20

// enum SafetyTriger
// {
//     NONE,
//     SENSOR_LEFT,
//     SENSOR_RIGHT,
//     SENSOR_BACK,
//     SENSOR_BACK_FLOW,
//     MENY_SENSORS
// };

class SafetyModule2
{
public:
    static SafetyModule2 &getInstance()
    {
        static SafetyModule2 instance;
        return instance;
    }
    long GetTics(bool left=true);
    void update();
    bool isBusy() const;
    void NewMov(MotionState Command, int Left = 0, int Right = 0);

private:
    SafetyModule2();
    MotionController motion;
    SurfaceSensor sensorLeft, sensorRight;
    SurfaceSensor sensorBack, sensorBackFlow;

    SafetyTriger sensorTrigger = SafetyTriger::NONE;

    UltrasonicModule ultrasonic; //(16,17);

    bool corection = false;

    bool CheckSensors();
    void Corection();
};