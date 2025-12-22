#pragma once
#include "../Core/EventBus.h"
#include "StateCommand.h"

enum StateID {
    STATE_START = 0,
    STATE_CALIBRATION = 1,
    STATE_NORMAL = 2,
    STATE_SLEEPY = 3,
    STATE_CLOCK  = 4
};

class State {
public:
    virtual ~State() {} 

    virtual void enter() {}
    virtual void update(float dt) {}
    virtual StateCommand handleEvent(Event e) { return CMD_NONE; }
    virtual void exit() {};
};
