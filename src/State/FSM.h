#pragma once
#include "State.h"
#include "Display/DisplaySystem.h"
#include "StateCommand.h"

class FSM {
public:
    FSM(State* initial, DisplaySystem* disp);

    void update(float dt);
    void handleEvent(Event e);
    void changeState(State* next);

private:
    State* current;
    DisplaySystem* display;
};