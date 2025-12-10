#include "SafetyModule.h"


#define MAX_STEEPS 10

class MovementModule {
private:
    SafetyModule& safety;

    int steep = 0;
    bool steepReady = true;
    bool ERROR_MOVE = false;
public:
    MovementModule(SafetyModule& s) : safety(s) {}

     void forward(int time = 20);
     void backward(int time = 20);
     void left(int time = 20);
     void right(int time = 20);
     void stop();
     void MoveDance(float dt);
};