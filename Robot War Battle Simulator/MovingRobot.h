#ifndef MOVINGROBOT_H
#define MOVINGROBOT_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Robot.h"

using namespace std;

class MovingRobot : virtual public Robot
{
protected:

public:
    virtual ~MovingRobot() {}

    virtual void robotMove() = 0;
};

#endif // MOVINGROBOT_H
