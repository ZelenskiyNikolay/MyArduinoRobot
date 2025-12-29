#ifndef MOVEMENT_REQUEST_H
#define MOVEMENT_REQUEST_H

enum class MoveType {
    Stop,
    Forward,
    Backward,
    Left,
    Right,
    Left90
};

struct MovementRequest {
    MoveType type =  MoveType::Stop;
    float time = 0; 

    //MovementRequest() = default;

    MovementRequest(MoveType t = MoveType::Stop, float dt = 20)
        : type(t), time(dt) {}
};
#endif // MOVEMENT_REQUEST_H