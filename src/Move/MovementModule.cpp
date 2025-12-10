#include "MovementModule.h"

void MovementModule::forward(int time = 20)
{
    safety.process(MovementRequest(MoveType::Forward, time));
}

void MovementModule::backward(int time = 20)
{
    safety.process(MovementRequest(MoveType::Backward, time));
}

void MovementModule::left(int time = 20)
{
    safety.process(MovementRequest(MoveType::Left, time));
}

void MovementModule::right(int time = 20)
{
    safety.process(MovementRequest(MoveType::Right, time));
}

void MovementModule::stop()
{
    safety.process(MovementRequest(MoveType::Stop, 0));
}