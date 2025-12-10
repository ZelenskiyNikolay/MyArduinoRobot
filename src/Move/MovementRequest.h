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
    MoveType type;
    float time; // 0–255 например

    MovementRequest(MoveType t, float dt = 20)
        : type(t), time(dt) {}
};
#endif // MOVEMENT_REQUEST_H