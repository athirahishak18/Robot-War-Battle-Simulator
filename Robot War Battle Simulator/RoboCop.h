#ifndef ROBOCOP_H
#define ROBOCOP_H

#include <iostream>

#include "SeeingRobot.h"
#include "ShootingRobot.h"
#include "MovingRobot.h"
#include "SteppingRobot.h"

using namespace std;

class RoboCop : public SeeingRobot, public ShootingRobot, public MovingRobot
{
private:
    static int incrementRobot_;
    bool upgraded_ = false;
public:
    RoboCop(string robotID = "", int x = -1, int y = -1);
    virtual ~RoboCop();
    static int incrementRobot();
    void setPosition(int x, int y);
    void robotLook();
    void robotShoot();
    void robotMove();
    virtual void actions();
    void upgrade();
};

#endif // ROBOCOP_H
