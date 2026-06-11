#include "Robot.h"
#include "Battlefield.h"
#include "RoboCop.h"
#include "Terminator.h"
#include "TerminatorRoboCop.h"
#include "BlueThunder.h"
#include "MadBot.h"
#include "RoboTank.h"
#include "UltimateRobot.h"

#include <iostream>
#include <vector>

using namespace std;

Robot::Robot(string robotID, int x, int y): robotID_(robotID), robotPositionX(x), robotPositionY(y) {}

int Robot::getX() const
{
    return robotPositionX;
}

int Robot::getY() const
{
    return robotPositionY;
}

void Robot::setPositionX(int x)
{
    robotPositionX = x;
}

void Robot::setPositionY(int y)
{
    robotPositionY = y;
}

string Robot::robotID() const
{
    return robotID_;
}

void Robot::setRobotID(string robotID)
{
    robotID_ = robotID;
}

string Robot::robotType() const
{
    return robotType_;
}

void Robot::setRobotType(string robotType)
{
    robotType_ = robotType;
}

string Robot::robotName() const
{
    return robotName_;
}

void Robot::setRobotName(string robotName)
{
    robotName_ = robotName;
}

int Robot::numOfLives() const
{
    return numOfLives_;
}

void Robot::setNumOfLives(int numOfLives)
{
    numOfLives_ = numOfLives;
}

void Robot::decrementLife()
{
    --numOfLives_;
}

int Robot::numOfKills() const
{
    return numOfKills_;
}

void Robot::setNumOfKills(int numOfKills)
{
    numOfKills_ = numOfKills;
}

void Robot::setGridDimensions(int cols, int rows)
{
    gridCols = cols;
    gridRows = rows;
}

void Robot::setBattlefield(const vector<vector<string>>& battlefield)
{
    battlefield_ = battlefield;
}

vector<vector<string>>& Robot::getBattlefield()
{
    return battlefield_;
}

void Robot::setRobots(vector<Robot*>* robots)
{
    robots_ = robots;  // Set pointer to Battlefield robots
}

void Robot::setAllRobots(vector<Robot*>* allRobots)
{
    allRobots_ = allRobots;
}

vector<Robot*>& Robot::getRobots()
{
    return *robots_;  // Dereference pointer
}

vector<Robot*>& Robot::getAllRobots()
{
    return *allRobots_;
}

void Robot::addDestroyedRobots(int x, int y)
{
    for (auto it = robots_->begin(); it != robots_->end(); )
    {
        if ((*it)->getX() == x && (*it)->getY() == y)
        {
            battlefield_[y][x] = "";

            // Decrement lives
            (*it)->decrementLife();

            if ((*it)->numOfLives() > 0)
            {
                waitingRobots.push((*it)->robotID());
                cout << endl << "Robot " << (*it)->robotID() << " has " << (*it)->numOfLives() << " lives left and is waiting to re-enter the battlefield." << endl;
            }

            else
            {
                cout << "Robot " << (*it)->robotID() << " has no lives left and is permanently destroyed." << endl;
                destroyedRobots.push((*it)->robotID());
            }

            for (auto& robot : *allRobots_)
            {
                if (robot->robotID() == (*it)->robotID())
                {
                    robot->setPositionX((*it)->getX());
                    robot->setPositionY((*it)->getY());
                    robot->setNumOfLives((*it)->numOfLives());
                    robot->setNumOfKills((*it)->numOfKills());
                    break;
                }
            }

            cout << "Deleted robot " << (*it)->robotID() << " from robots vector" << endl << endl;

            delete *it;
            it = robots_->erase(it);
        }

        else
        {
            ++it;
        }
    }
}

void Robot::recoverRobot()
{
    // Check waiting robots
    while (!waitingRobots.empty())
    {

        string robotID = waitingRobots.front();  // Get the robot ID from the queue
        waitingRobots.pop();  // Remove the robot ID from the queue
        cout << "Recovering robot with ID: " << robotID << endl;

        for (auto it = allRobots_->begin(); it != allRobots_->end(); ++it)
        {
            if ((*it)->robotID() == robotID)
            {
                if ((*it)->numOfLives() > 0)
                {
                    int x, y;
                    do
                    {
                        x = rand() % gridCols;
                        y = rand() % gridRows;
                    } while (battlefield_[y][x] != "");

                    // Set the recovered robot's new position
                    (*it)->setPositionX(x);
                    (*it)->setPositionY(y);

                    // Add the recovered robot back to the robots vector
                    robots_->push_back(*it);

                    battlefield_[y][x] = robotID;  // Update the battlefield with the robot ID
                    cout << "Robot " << robotID << " has been recovered and placed at (" << x << ", " << y << ") with " << (*it)->numOfLives() << " lives left." << endl;
                }
                else
                {
                    cout << "Robot " << robotID << " has no lives left and cannot be recovered." << endl;
                }

                break;  // Exit the loop after processing the robot
            }
        }
    }
}

ostream& operator <<(ostream &out, const Robot& r)
{
    out << r.robotID_ << " at (" << r.robotPositionX << ", " <<  r.robotPositionY <<")";
    return out;
}

int Robot::gridCols = 0;
int Robot::gridRows = 0;
vector<vector<string>> Robot::battlefield_;
vector<Robot*>* Robot::robots_ = nullptr;
vector<Robot*>* Robot::allRobots_ = nullptr;
Queue Robot::destroyedRobots;
Queue Robot::waitingRobots;
