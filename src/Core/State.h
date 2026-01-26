#pragma once
#include "EventBus.h"
//#include "FSM.h"
//#include "StateCommand.h"

enum StateID {
    STATE_START = 0,
    STATE_CALIBRATION = 1,
    STATE_NORMAL = 2,
    STATE_SLEEPY = 3,
    STATE_CLOCK  = 4,
    STATE_SEARCH_BASE = 5
};

// enum StateCommand {
//     CMD_NONE = 0,
//     CMD_TO_CALIBRATION,
//     CMD_TO_NORMAL,
//     CMD_TO_SLEEPY,
//     CMD_TO_ANGRY,
//     CMD_TO_HAPPY
// };

class State {
public:
    virtual ~State() {} 

    virtual void enter() {}
    virtual void update(float dt) {}
    //virtual StateCommand handleEvent(Event e) { return CMD_NONE; }
    virtual void exit() {};
};
