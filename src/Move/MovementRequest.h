#ifndef MOVEMENT_REQUEST_H
#define MOVEMENT_REQUEST_H

enum class MoveType
{
    Stop,
    Forward = -1,
    Backward = 1,
    Left = 2,
    Right = 3,
    Left90 = 4,
    ForwardSteeps = 5
};

struct MovementRequest
{
    MoveType type = MoveType::Stop;
    float time = 0;

    // MovementRequest() = default;

    MovementRequest(MoveType t = MoveType::Stop, float dt = 20)
        : type(t), time(dt) {}
};
#endif // MOVEMENT_REQUEST_H