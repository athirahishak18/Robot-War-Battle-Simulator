#ifndef SHOOTINGROBOT_H
#define SHOOTINGROBOT_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Robot.h"

using namespace std;

class ShootingRobot : virtual public Robot
{
protected:

public:
    virtual ~ShootingRobot() {}

    virtual void robotShoot() = 0;
};

#endif // SHOOTINGROBOT_H
