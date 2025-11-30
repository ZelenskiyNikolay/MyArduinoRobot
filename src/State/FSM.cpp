#include "FSM.h"
#include "StateNormal.h"
#include "StateSleepy.h"
#include "StateCommand.h"

FSM::FSM(State *initial, DisplaySystem *disp)
    : current(initial), display(disp)
{
    current->enter();
}

void FSM::update(float dt)
{
    if (!current) return;
    current->update(dt);
}

void FSM::handleEvent(Event e)
{
    StateCommand cmd = current->handleEvent(e);

    switch (cmd)
    {
    case CMD_TO_NORMAL:
        changeState(new StateNormal(*display));
        break;

    case CMD_TO_SLEEPY:
        changeState(new StateSleepy(*display));
        break;

    default:
        break;
    }
}

void FSM::changeState(State *next)
{
    delete current;
    current = next;
    current->enter();
}
