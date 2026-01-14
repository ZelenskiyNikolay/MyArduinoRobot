#pragma once
#include "MotorModule.h"
#include "MovementRequest.h"
#include "Sensors/SurfaceSensor.h"
#include "Sensors/UltrasonicSensor.h"
#include "Sensors/RPM_sensor.h"

#define ticks90Left 18
#define ticks90Right 20

enum SafetyTriger
{
    NONE,
    SENSOR_LEFT,
    SENSOR_RIGHT,
    SENSOR_BACK,
    SENSOR_BACK_FLOW,
    MENY_SENSORS
};
enum Wheel
{
    LEFT,
    RIGHT
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

    RPM_sensor leftEnc;  // INT5
    RPM_sensor rightEnc; // INT4

    int prevLeftTicks = 0;
    int prevRightTicks = 0;

    float timer = 200;

public:
    static SafetyModule &getInstance()
    {
        static SafetyModule instance;
        return instance;
    }

    void startRequest(const MovementRequest &req);
    int update(float dt);
    bool isBusy() const;
    void STOP_MOTORS();
    void reset();
    long GetTics(bool left = true);
    void ResetStips();
    int GetCorrections(bool left = true);
    void ResetCorrections();
    void CorrectMove();
    int Turn90Left();
    int Turn90Right();

    float GetDistance();
    void TriggerUltrasonic();

    int FinalAlign();
    void StartFinalAlign();

    int Forward(int Left, int Right);
    int ForwardSteeps();
private:
    void process(const MovementRequest &req);

    SafetyModule();
    bool CheckSensors();
    SafetyTriger sensorTrigger = SafetyTriger::NONE;
    bool corection = false;
    int alignTarget = 0;
    bool alignActive = false;
    int alignLeftStart;
    int alignRightStart;
    int alignWheel;
    int SteepsLeft;
    int SteepsRight;
};