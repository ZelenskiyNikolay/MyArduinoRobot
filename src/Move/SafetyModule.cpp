#include "SafetyModule.h"

void SafetyModule::process(const MovementRequest &req)
{
    motor.execute(req);
}