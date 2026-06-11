#ifndef TERMINATOR_H
#define TERMINATOR_H

#include <iostream>

#include "SeeingRobot.h"
#include "ShootingRobot.h"
#include "MovingRobot.h"
#include "SteppingRobot.h"

using namespace std;

class Terminator : public SeeingRobot, public SteppingRobot
{
private:
    static int incrementRobot_;
    bool upgraded_ = false;
    static vector<pair<int, int>> enemyPositions;

public:
    Terminator(string robotID = "", int x = -1, int y = -1);
    virtual ~Terminator();
    static int incrementRobot();
    virtual void setPosition(int x, int y);
    void robotLook() ;
    void robotStep();
    virtual void actions();
    void upgrade();
};

#endif // TERMINATOR_H
