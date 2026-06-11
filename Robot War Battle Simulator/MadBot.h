#ifndef MADBOT_H
#define MADBOT_H

#include <iostream>

#include "SeeingRobot.h"
#include "ShootingRobot.h"
#include "MovingRobot.h"
#include "SteppingRobot.h"

using namespace std;

class MadBot : public ShootingRobot
{
private:
    static int incrementRobot_;
    bool upgraded_ = false;

public:
    MadBot(string robotID = "", int x = -1, int y = -1);
    virtual ~MadBot() {}
    static int incrementRobot();
    virtual void setPosition(int x, int y);
    void robotShoot();
    virtual void actions();
    void upgrade();
};

#endif // MADBOT_H
