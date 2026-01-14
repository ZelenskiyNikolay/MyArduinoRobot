#include "MotionController.h"

MotionController::MotionController()
    : motor(), leftEnc(18), rightEnc(19)
{
    leftEnc.begin();
    rightEnc.begin();
}

long MotionController::GetTics(bool left)
{
    if (left)
    {
        return leftEnc.GetSensorState();
    }
    else
    {
        return rightEnc.GetSensorState();
    }
}
void MotionController::NewMov(MotionState Command, int Left, int Right)
{
    switch (Command)
    {
    case MotionState::IDLE:
        motor.stop();
        command.type = Command;
        break;
    case MotionState::FORWARD:
        command.startLeft = GetTics();
        command.startRight = GetTics(false);
        command.targetLeft = Left;
        command.targetRight = Right;
        command.type = Command;
        break;
    case MotionState::BACKWARD:
        command.startLeft = GetTics();
        command.startRight = GetTics(false);
        command.targetLeft = Left;
        command.targetRight = Right;
        command.type = Command;
        break;
    case MotionState::TURN_LEFT90:
        command.startLeft = GetTics();
        command.startRight = GetTics(false);
        command.targetLeft = Left;
        command.targetRight = Right;
        command.type = Command;
        break;
        // case MotionState::IDLE:
        //     motor.stop();
        // break;
    }
}

int MotionController::update()
{
    if (command.type == IDLE)
        return 1;

    long dl = GetTics() - command.startLeft;
    long dr = GetTics(false) - command.startRight;

    switch (command.type)
    {
    case FORWARD:
        ForwardMov(dl, dr);
        break;
    case BACKWARD:
        BackwardMov(dl, dr);
        break;
    case TURN_LEFT90:
        Turn90Left(dl);
        break;
    }
    return -1;
}

void MotionController::Turn90Left(long dl)
{
    if (dl >= ticks90Left)
    {
        motor.stop();
        command.type = IDLE;
        return;
    }
    motor.left(); // правое вперёд, левое назад
}
void MotionController::BackwardMov(long dl, long dr)
{
    if (dl >= command.targetLeft)
        motor.stopLeft();
    else
        motor.backwardLeft();

    if (dr >= command.targetRight)
        motor.stopRight();
    else
        motor.backwardRight();

    if (dl >= command.targetLeft && dr >= command.targetRight)
    {
        motor.stop();
        command.type = IDLE;
    }
}
void MotionController::ForwardMov(long dl, long dr)
{
    if (dl >= command.targetLeft)
        motor.stopLeft();
    else
        motor.forwardLeft();

    if (dr >= command.targetRight)
        motor.stopRight();
    else
        motor.forwardRight();

    if (dl >= command.targetLeft && dr >= command.targetRight)
    {
        motor.stop();
        command.type = IDLE;
    }
}
bool MotionController::isBusy() const
{
    if (command.type == IDLE)
        return false;
    else
        return true;
}
void MotionController::SafatyStop()
{
    motor.stop();
    command.type = IDLE;
}