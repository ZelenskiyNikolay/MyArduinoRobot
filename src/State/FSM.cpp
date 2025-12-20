#include "FSM.h"
#include "StateNormal.h"
#include "StateSleepy.h"
#include "StateCommand.h"
#include "StateClock.h"

FSM::FSM(State *initial, DisplaySystem *dispOld)
    : current(initial), displayOld(dispOld)
{
    current->enter();
}
FSM::FSM(State *initial, DisplayOled *disp)
    : current(initial), display(disp)
{
    current->enter();
}


void FSM::Init(State *initial, DisplayOled *disp)
{
    current = initial;
    display = disp;
}

void FSM::update(float dt)
{
    if (!current) return;
    current->update(dt);
}

void FSM::handleEvent(Event e)
{
    StateCommand cmd = current->handleEvent(e);

    switch(e.type)
    {
        case EVENT_CHANGE_STATE:
            changeStateById((StateID)e.data);
            break;

        // другие события…
    }

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

void FSM::changeStateById(StateID id)
{
    //Останавливаем моторы при смене состояния
    SafetyModule::getInstance().STOP_MOTORS();
    MovementModule::getInstance().stop();
    
    if(GlobalSettings::getInstance().NOT_CHENGE_STATE && 
    !GlobalSettings::getInstance().STATE_START)//если менять состояние нельзя
        return;
    if(GlobalSettings::getInstance().STATE_START)
        GlobalSettings::getInstance().STATE_START=false;

    switch(id) {
        case STATE_NORMAL:
            changeState(new StateNormal(*display));
            break;

        case STATE_SLEEPY:
            changeState(new StateSleepy(*display));
            break;

        case STATE_CLOCK:
            changeState(new StateClock(*display));
            break;
    }
}