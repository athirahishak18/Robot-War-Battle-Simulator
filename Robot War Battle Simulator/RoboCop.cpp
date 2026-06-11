#include <iostream>
#include "RoboCop.h"
#include "TerminatorRoboCop.h"

using namespace std;

int RoboCop::incrementRobot_ = 0;

    RoboCop::~RoboCop() {}

    RoboCop::RoboCop(string robotID, int x, int y) : Robot(robotID, x, y)
    {
       incrementRobot_++;
    }

    int RoboCop::incrementRobot()
    {
        return incrementRobot_;
    }

    void RoboCop::setPosition(int x, int y)
    {
        setPositionX(x);
        setPositionY(y);
    }

    void RoboCop::robotLook()
    {
        bool foundEnemy = false;
        cout << robotID() << " is looking around." << endl;
        // Logic to check the 8 neighboring cells
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0)
                {
                    continue;
                }

                int newX = getX() + dx;
                int newY = getY() + dy;

                if (newX >= 0 && newX < gridCols && newY >= 0 && newY < gridRows)
                {
                    if (!Robot::battlefield_[newY][newX].empty())
                    {
                        cout << "Enemy detected at (" << newX << ", " << newY << ")" << endl;
                        foundEnemy = true;
                    }
                }
            }
        }

        if (!foundEnemy)
        {
            cout << "No enemies detected" << endl;
        }
    }

    void RoboCop::robotShoot()
    {
        const int MAX_DISTANCE = 10;
        const int NUM_SHOTS = 3;
        int shotsFired = 0;

        while (shotsFired < NUM_SHOTS)
        {
            int deltaX = rand() % (2 * MAX_DISTANCE + 1) - MAX_DISTANCE; // Random number between -10 and 10
            int deltaY = rand() % (2 * MAX_DISTANCE + 1) - MAX_DISTANCE;
            int targetX = getX() + deltaX;
            int targetY = getY() + deltaY;

            if (targetX >= 0 && targetX < gridCols && targetY >= 0 && targetY < gridRows && !(targetX == getX() && targetY == getY()))
            {
                cout << "RoboCop fires at (" << targetX << ", " << targetY << ")." << endl;

                if(!Robot::battlefield_[targetY][targetX].empty())
                {
                    cout << "Enemy at (" << targetX << ", " << targetY << ") has been killed." << endl;

                    addDestroyedRobots(targetX, targetY);

                    numOfKills_++;
                }
                shotsFired++;
            }
        }
    }

    void RoboCop::robotMove()
    {
        int newX, newY;
        do
        {
            newX = getX() + (rand() % 3) - 1;  // Generate random number between -1 and 1
            newY = getY() + (rand() % 3) - 1;
        } while ((newX == getX() && newY == getY()) || newX < 0 || newX >= gridCols || newY < 0 || newY >= gridRows || !Robot::battlefield_[newY][newX].empty());

        // Clear the old position on the battlefield grid
        Robot::battlefield_[getY()][getX()] = "";

        setPositionX(newX);
        setPositionY(newY);

        Robot::battlefield_[newY][newX] = robotID_;

        cout << robotID() << " moved to (" << newX << ", " << newY << ")." << endl << endl;
    }

    void RoboCop::actions()
    {
        robotLook();
        robotShoot();
        robotMove();

        if (numOfKills_ == 3 && !upgraded_)
        {
            upgrade();
            upgraded_ = true;
        }


        for (auto& robot : *allRobots_)
        {
            if (robot->robotID() == robotID_)
            {
                robot->setPositionX(getX());
                robot->setPositionY(getY());
                robot->setNumOfLives(numOfLives()); // Synchronize lives
                robot->setNumOfKills(numOfKills()); // Synchronize kills
                break;
            }
        }
    }

    void RoboCop::upgrade()
    {
        int terminatorRoboCopCount = 0;

        for (auto robot : *robots_)
        {
            if (dynamic_cast<TerminatorRoboCop*>(robot) != nullptr)
            {
                terminatorRoboCopCount++;
            }
        }

        if (numOfKills_ == 3)
        {
            int x = getX();
            int y = getY();

            string currentRobot = robotID();

            // Create a new robot ID
            /*string newRobotID = "TR0" + to_string(terminatorRoboCopCount + 1);
            cout << "Upgrading " << robotID() << " to " << newRobotID << endl;

            // Create a new TerminatorRoboCop instance
            TerminatorRoboCop* newRobot = new TerminatorRoboCop(newRobotID, x, y);

            // Replace current RoboCop in the battlefield
            for (auto it = robots_->begin(); it != robots_->end();)
            {
                if ((*it)->robotID() == robotID())
                {
                    // Remove current instance from the battlefield
                    Robot::battlefield_[(*it)->getY()][(*it)->getX()] = "";


                    // Delete current instance
                    delete *it;
                    it = robots_->erase(it); // Erase and get the next valid iterator

                    // Add the new robot to the robots_ vector
                    robots_->push_back(newRobot);
                    allRobots_->push_back(newRobot);

                    // Update battlefield
                    if (y < Robot::battlefield_.size() && x < Robot::battlefield_[0].size())
                    {
                        Robot::battlefield_[y][x] = newRobotID;
                    }
                    else
                    {
                        cout << "Error: Invalid location for the robot " << newRobotID << endl;
                    }

                    break;
                }
                else
                {
                    ++it;
                }
            }*/
        }
    }
