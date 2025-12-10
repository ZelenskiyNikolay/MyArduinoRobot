#include "SafetyModule.h"

SafetyModule::SafetyModule(MotorModule& motor)
    : motor(motor) {}

void SafetyModule::process(const MovementRequest &req)
{
    motor.execute(req);
}

void SafetyModule::startRequest(const MovementRequest& req) {
    current = req;
    elapsed = 0;
    active = true;

    switch (req.type) {
        case MoveType::Forward:  motor.forward(); break;
        case MoveType::Backward: motor.backward(); break;
        case MoveType::Left:     motor.left(); break;
        case MoveType::Right:    motor.right(); break;
        default: break;
    }
}

bool SafetyModule::update(unsigned long dt) {
    if (!active) return false;

    // Здесь можно добавить проверки датчиков безопасности
    // if (detectObstacle()) {
    //     motor.stop();
    //     active = false;
    //     return true;  // завершено аварийно
    // }

    elapsed += dt;
    if (elapsed >= current.time) {
        motor.stop();
        active = false;
        return true; // завершено по времени
    }

    return false; // еще выполняется
}

bool SafetyModule::isBusy() const {
    return active;
}
