#include "SafetyModule.h"

SafetyModule::SafetyModule()
    : sensorLeft(36), sensorRight(38), sensorBack(14), sensorBackFlow(15),
      ultrasonic(28, 3), motion()
{
    ultrasonic.begin();
    CheckSensors();
}

void SafetyModule::TriggerUltrasonic() { ultrasonic.Trigger(); }
float SafetyModule::GetDistance() { return ultrasonic.getDistance(); }

void SafetyModule::update()
{
    if (corection)
    {
        CheckSensors();
        Corection();
        motion.update();
        return;
    }
    if (CheckSensors())
    {
        // завершено аварийно
        motion.SafatyStop();
        corection = true;
    }
    else
    {
        motion.update();
    }
}
bool SafetyModule::EdgeAlignment()
{
    bool Left = sensorLeft.GetSensorState();
    bool Right = sensorRight.GetSensorState();

    if (Left && Right)
    {
        motion.Forward();
    }
    if (!Left)
    {
        motion.LeftStop();
    }
    if (!Right)
    {
        motion.RightStop();
    }
    if (!Left && !Right)
    {
        motion.SafatyStop();
        return true;
    }
    return false;
}
void SafetyModule::Corection()
{
    switch (sensorTrigger)
    {
    case SafetyTriger::SENSOR_LEFT:
        NewMov(MotionState::BACKWARD, 3, 3);
        break;
    case SafetyTriger::SENSOR_RIGHT:
        NewMov(MotionState::BACKWARD, 3, 3);
        break;
    case SafetyTriger::SENSOR_BACK:
        NewMov(MotionState::FORWARD, 3, 3);
        break;
    case SafetyTriger::SENSOR_BACK_FLOW:
        NewMov(MotionState::FORWARD, 3, 3);
        break;
    case SafetyTriger::NONE:
        corection = false;
        break;
    default:
        break;
    }
}

bool SafetyModule::CheckSensors()
{
    bool Left = sensorLeft.GetSensorState();
    bool Right = sensorRight.GetSensorState();
    bool BackFlow = sensorBackFlow.GetSensorState();
    bool Back = sensorBack.GetSensorState();
    if (Left && Right && BackFlow && !Back)
        sensorTrigger = SafetyTriger::NONE;
    else if (!Left)
        sensorTrigger = SafetyTriger::SENSOR_LEFT;
    else if (!Right)
        sensorTrigger = SafetyTriger::SENSOR_RIGHT;
    else if (!BackFlow)
        sensorTrigger = SafetyTriger::SENSOR_BACK_FLOW;
    else if (Back)
        sensorTrigger = SafetyTriger::SENSOR_BACK;

    return (!Left || !Right || !BackFlow || Back);
}

bool SafetyModule::isBusy() const
{
    return motion.isBusy();
}
void SafetyModule::NewMov(MotionState Command, int Left, int Right)
{
    motion.NewMov(Command, Left, Right);
}
long SafetyModule::GetTics(bool left) { return motion.GetTics(left); }
void SafetyModule::StopMov(){ motion.SafatyStop();}