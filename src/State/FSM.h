#pragma once
#include "State.h"
#include "Display/DisplaySystem.h"
#include "Display/DisplayOled.h"
#include "StateCommand.h"


class FSM {
public:
    FSM(State* initial, DisplaySystem* dispOld);
    FSM(State* initial, DisplayOled* disp);
    
    void Init(State *initial, DisplayOled *disp);

    void update(float dt);
    void handleEvent(Event e);
    void changeState(State* next);
    void changeStateById(StateID id);
private:
    State* current;
    DisplaySystem* displayOld;
    DisplayOled* display;
};