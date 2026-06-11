#ifndef STEPPINGROBOT_H
#define STEPPINGROBOT_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Robot.h"

using namespace std;

class SteppingRobot : virtual public Robot
{
protected:

public:
    virtual ~SteppingRobot() {}

    virtual void robotStep() = 0;
};

#endif // STEPPINGROBOT_H
