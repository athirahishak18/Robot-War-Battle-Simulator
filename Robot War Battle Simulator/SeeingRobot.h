#ifndef SEEINGROBOT_H
#define SEEINGROBOT_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Robot.h"

using namespace std;

class SeeingRobot : virtual public Robot
{
protected:

public:
    virtual ~SeeingRobot() {}

    virtual void robotLook() = 0;
};

#endif // SEEINGROBOT_H
