#pragma once
#include "../Core/EventBus.h"
#include "StateCommand.h"

class State {
public:
    virtual ~State() {} 

    virtual void enter() {}
    virtual void update(float dt) {}
    virtual StateCommand handleEvent(Event e) { return CMD_NONE; }
    virtual void exit() {};
};
