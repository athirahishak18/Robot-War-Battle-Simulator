#ifndef ULTIMATEROBOT_H
#define ULTIMATEROBOT_H

#include <iostream>

#include "SeeingRobot.h"
#include "ShootingRobot.h"
#include "MovingRobot.h"
#include "SteppingRobot.h"

using namespace std;

class UltimateRobot : public SeeingRobot, public ShootingRobot, public SteppingRobot
{
private:
    static int incrementRobot_;
    static vector<pair<int, int>> enemyPositions;

public:
    UltimateRobot(string robotID = "", int x = -1, int y = -1);
    virtual ~UltimateRobot() {}
    static int incrementRobot();
    void setPosition(int x, int y);
    void robotLook();
    void robotShoot();
    void robotStep();
    virtual void actions();
    void upgrade();
};

#endif // ULTIMATEROBOT_H
