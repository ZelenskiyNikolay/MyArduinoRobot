#ifndef MOVEMENT_REQUEST_H
#define MOVEMENT_REQUEST_H

enum class MoveType {
    Stop,
    Forward,
    Backward,
    Left,
    Right
};

struct MovementRequest {
    MoveType type =  MoveType::Stop;
    float time = 0; 

    MovementRequest() = default;

    MovementRequest(MoveType t, float dt = 20)
        : type(t), time(dt) {}
};
#endif // MOVEMENT_REQUEST_H