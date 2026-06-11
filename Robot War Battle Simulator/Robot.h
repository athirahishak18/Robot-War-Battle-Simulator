#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Queue.h"

using namespace std;

class Robot
{
protected:
    int robotPositionX = -1;
    int robotPositionY = -1;;
    string robotID_ = "";
    string robotType_ = "";
    string robotName_ = "";
    int numOfLives_ = 2;
    int numOfKills_ = 0;
    static int gridCols;
    static int gridRows;
    static vector<vector<string>> battlefield_;
    static vector<Robot*>* robots_;
    static vector<Robot*>* allRobots_;

public:
    Robot(string robotID ="", int x = -1, int y = -1);
    virtual ~Robot() = default;
    static Queue destroyedRobots;
    static Queue waitingRobots; // Queue for robots waiting to re-enter battlefield
    int getX() const;
    int getY() const;
    void setPositionX(int x);
    void setPositionY(int y);
    string robotID() const;
    void setRobotID(string robotID);
    string robotType() const;
    void setRobotType(string robotType);
    string robotName() const;
    void setRobotName(string robotName);
    int numOfLives() const;
    void setNumOfLives(int numOfLives);
    void decrementLife();
    int numOfKills() const;
    void setNumOfKills(int numOfKills);
    virtual void actions() = 0;
    static void setGridDimensions(int cols, int rows);
    static void setBattlefield(const vector<vector<string>>& battlefield);
    static vector<vector<string>>& getBattlefield();
    static void setRobots(vector<Robot*>* robots);
    static void setAllRobots(vector<Robot*>* allRobots);
    static vector<Robot*>& getRobots();
    static vector<Robot*>& getAllRobots();
    static void addDestroyedRobots(int x, int y);
    static void recoverRobot();
    friend ostream& operator <<(ostream &out, const Robot& r);
};

#endif // ROBOT_H
