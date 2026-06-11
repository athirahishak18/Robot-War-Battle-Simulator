#ifndef BLUETHUNDER_H
#define BLUETHUNDER_H

#include <iostream>

#include "SeeingRobot.h"
#include "ShootingRobot.h"
#include "MovingRobot.h"
#include "SteppingRobot.h"

using namespace std;

class BlueThunder : public ShootingRobot
{
private:
    static int incrementRobot_;
    int currentShotIndex;
    bool upgraded_ = false;

public:
    BlueThunder(string robotID = "", int x = -1, int y = -1);
    ~BlueThunder() override{}
    static int incrementRobot();
    virtual void setPosition(int x, int y);
    void robotShoot() override;
    virtual void actions() override;
    void upgrade();
};

#endif // BLUETHUNDER_H
