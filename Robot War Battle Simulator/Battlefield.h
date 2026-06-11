#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Robot.h"
#include "Queue.h"

using namespace std;

class Battlefield
{
protected:
    int NUM_OF_ROW_ = -1;
    int NUM_OF_COLUMN_ = -1;
    int numOfRobots_ = -1;

    vector<Robot*> robots_;
    vector<Robot*> allRobots_;
    vector<vector<string>> battlefield_;
    Queue destroyedRobots; // Add this line

public:
    int turns_ = -1;
    Queue& getDestroyedRobots();
    Battlefield();
    ~Battlefield();
    int NUM_OF_COLUMN();
    int NUM_OF_ROW();
    int turns();
    int numOfRobots();
    vector<Robot*> robots();
    vector<Robot*> allRobots();
    vector<vector<string>> battlefield();
    vector<Robot*>& getRobots();
    vector<Robot*>& getAllRobots();
    void readFile(string file);
    void placeRobots();
    void printRobots();
    void displayGrid() const;
    void robotActions();
    void recoverRobot();
    void outputFile(string) const;
};

#endif // BATTLEFIELD_H
