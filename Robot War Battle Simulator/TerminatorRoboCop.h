#ifndef TERMINATORROBOCOP_H
#define TERMINATORROBOCOP_H

#include <iostream>

#include "SeeingRobot.h"
#include "ShootingRobot.h"
#include "MovingRobot.h"
#include "SteppingRobot.h"

using namespace std;

class TerminatorRoboCop : public SeeingRobot, public ShootingRobot, public SteppingRobot
{
private:
    static int incrementRobot_;
    bool upgraded_ = false;
    static vector<pair<int, int>> enemyPositions;

public:
    TerminatorRoboCop(string robotID = "", int x = -1, int y = -1);
    ~TerminatorRoboCop() override{}
    static int incrementRobot();
    virtual void setPosition(int x, int y);
    void robotLook();
    void robotShoot();
    void robotStep();
    virtual void actions();
    void upgrade();
};

#endif // TERMINATORROBOCOP_H
