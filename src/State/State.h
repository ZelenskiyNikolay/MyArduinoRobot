#pragma once
#include "../Core/EventBus.h"
#include "StateCommand.h"

enum StateID {
    STATE_NORMAL = 0,
    STATE_SLEEPY = 1,
    STATE_CLOCK  = 2
};

class State {
public:
    virtual ~State() {} 

    virtual void enter() {}
    virtual void update(float dt) {}
    virtual StateCommand handleEvent(Event e) { return CMD_NONE; }
    virtual void exit() {};
};
