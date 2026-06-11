#ifndef ROBOTANK_H
#define ROBOTANK_H

#include <iostream>

#include "SeeingRobot.h"
#include "ShootingRobot.h"
#include "MovingRobot.h"
#include "SteppingRobot.h"

using namespace std;

class RoboTank : public ShootingRobot
{
private:
    static int incrementRobot_;
    bool upgraded_ = false;

public:
    RoboTank(string robotID = "", int x = -1, int y = -1);
    virtual ~RoboTank() {}
    static int incrementRobot();
    virtual void setPosition(int x, int y);
    void robotShoot();
    virtual void actions();
    void upgrade();
};

#endif // ROBOTANK_H
