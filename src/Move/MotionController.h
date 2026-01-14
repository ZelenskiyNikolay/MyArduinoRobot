#pragma once
#include "MotorModule.h"
#include "Sensors/RPM_sensor.h"

#define ticks90Left 18
#define ticks90Right 20

enum MotionState {
    IDLE,
    FORWARD,
    BACKWARD,
    TURN_LEFT90,
    TURN_RIGHT90
};
struct MotionCommand {
    MotionState type;
    long targetLeft;
    long targetRight;
    long startLeft;
    long startRight;
};

class MotionController
{
private:
    MotorModule motor;

    RPM_sensor leftEnc;  // INT5
    RPM_sensor rightEnc; // INT4

    int SteepsLeft;
    int SteepsRight;

    bool active = false;

    MotionCommand command;

    void ForwardMov(long dl,long dr);
    void BackwardMov(long dl, long dr);
    void Turn90Left(long dl);
public:
    MotionController();
    int update();
    bool isBusy() const;
    void NewMov(MotionState Command,int Left=0,int Right=0);
    int Forward(int Left, int Right);
    int ForwardSteeps();
    void SafatyStop();
    

    long GetTics(bool left = true);
};