#include "SafetyModule.h"


class MovementModule {
private:
    SafetyModule& safety;

public:
    MovementModule(SafetyModule& s) : safety(s) {}

     void forward(int time = 20);
     void backward(int time = 20);
     void left(int time = 20);
     void right(int time = 20);
     void stop();
};