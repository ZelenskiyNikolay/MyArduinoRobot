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
    case MotionState::TURN_LEFT:
        command.startLeft = GetTics();
        command.startRight = GetTics(false);
        command.targetLeft = Left;
        command.type = Command;
        break;
    case MotionState::TURN_RIGHT:
        command.startLeft = GetTics();
        command.startRight = GetTics(false);
        command.targetRight = Right;
        command.type = Command;
        break;
    case MotionState::TURN_LEFT90:
        command.startLeft = GetTics();
        command.startRight = GetTics(false);
        command.type = Command;
        break;
    case MotionState::TURN_RIGHT90:
        command.startLeft = GetTics();
        command.startRight = GetTics(false);
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
    case TURN_LEFT:
        if (command.targetLeft > 2)
            TurnLeft(dl,dr, command.targetLeft);
        else
            TurnLeft(dl,dr);
        break;
    case TURN_RIGHT:
        if (command.targetRight > 2)
            TurnRight(dl,dr, command.targetRight);
        else
            TurnRight(dl,dr);
        break;
    case TURN_LEFT90:
        Turn90Left(dl,dr);
        break;
    case TURN_RIGHT90:
        Turn90Right(dl,dr);
        break;
    case IDLE:
        break;
    }
    return -1;
}
void MotionController::TurnRight(long dl,long dr, int ticks)
{
    if (dr >= ticks)
    {
        motor.stopRight();
    }
    else{ motor.backwardRight();}
    if (dl >= ticks)
    {
        motor.stopLeft();
    }
    else{ motor.forwardLeft();}

    if (dr >= ticks && dl >= ticks)
    {
        motor.stop();
        command.type = IDLE;
    }
}
void MotionController::TurnLeft(long dl,long dr, int ticks)
{
    if (dl >= ticks)
    {
        motor.stopLeft();
    }
    else{ motor.backwardLeft();}
    if (dr >= ticks)
    {
        motor.stopRight();
    }
    else{ motor.forwardRight();}

    if (dr >= ticks && dl >= ticks)
    {
        motor.stop();
        command.type = IDLE;
    }
}
void MotionController::Turn90Right(long dl,long dr)
{
    if (dr >= ticks90Right)
    {
        motor.stopRight();
    }
    else{ motor.backwardRight();}
    if (dl >= ticks90Left)
    {
        motor.stopLeft();
    }
    else{ motor.forwardLeft();}

    if (dr >= ticks90Right && dl >= ticks90Left)
    {
        motor.stop();
        command.type = IDLE;
        return;
    }
}
void MotionController::Turn90Left(long dl,long dr)
{
    if (dl >= ticks90Left)
    {
        motor.stopLeft();
    }
    else{ motor.backwardLeft();}
    if (dr >= ticks90Right)
    {
        motor.stopRight();
    }
    else{ motor.forwardRight();}

    if (dr >= ticks90Right && dl >= ticks90Left)
    {
        motor.stop();
        command.type = IDLE;
        return;
    }
}
void MotionController::BackwardMov(long dl, long dr)
{
    if (dl - dr > 1 && motor.corrLeft > 0)
    {
        motor.corrLeft--;
    }
    else if (dl - dr < -1 && motor.corrLeft < MAX_CORR)
    {
        motor.corrLeft++;
    }

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
    if (dl - dr > 1 && motor.corrLeft > 0)
    {
        motor.corrLeft--;
    }
    else if (dl - dr < -1 && motor.corrLeft < MAX_CORR)
    {
        motor.corrLeft++;
    }


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
        Serial.print("Correction ");
        Serial.println(motor.corrLeft);
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
    // command.type = IDLE;
}
void MotionController::Forward() { motor.forward(); }
void MotionController::LeftStop() { motor.stopLeft(); }
void MotionController::RightStop() { motor.stopRight(); }