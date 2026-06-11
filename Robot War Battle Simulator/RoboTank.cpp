#include <iostream>
#include "RoboTank.h"
#include "UltimateRobot.h"

using namespace std;

int RoboTank::incrementRobot_= 0;

    RoboTank::RoboTank(string robotID, int x, int y) : Robot(robotID, x, y)
    {
        incrementRobot_++;
    }

    int RoboTank::incrementRobot()
    {
        return incrementRobot_;
    }

    void RoboTank::setPosition(int x, int y)
    {
        setPositionX(x);
        setPositionY(y);
    }

    void RoboTank::robotShoot()
    {
        const int NUM_SHOTS = 1;
        int shotsFired = 0;

        while (shotsFired < NUM_SHOTS)
        {
            int deltaX, deltaY;

            do
            {
                deltaX = rand() % gridCols;
                deltaY = rand() % gridRows;
            } while (deltaX == getX() && deltaY == getY());

            if (deltaX >= 0 && deltaX < gridCols && deltaY >= 0 && deltaY < gridRows && !(deltaX == getX() && deltaY == getY()))
            {
                cout << "RoboTank fires at (" << deltaX << ", " << deltaY << ")." << endl;

                if(!Robot::battlefield_[deltaY][deltaX].empty())
                {
                    cout << "Enemy at (" << deltaX << ", " << deltaY << ") has been killed." << endl;
                    addDestroyedRobots(deltaX, deltaY);
                    numOfKills_++;
                }
                shotsFired++;
            }
        }
    }

    void RoboTank::actions()
    {
        robotShoot();

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

    void RoboTank::upgrade()
    {
        int ultimateRobotCount = 0;

        // Count existing UltimateRobot
        for (auto robot : *robots_)
        {
            if (dynamic_cast<UltimateRobot*>(robot) != nullptr)
            {
                ultimateRobotCount++;
            }
        }

        if (numOfKills_ == 3)
        {
            int x = getX();
            int y = getY();

            string currentRobot = robotID();

            // Create a new robot ID
            /*string newRobotID = "UR0" + to_string(ultimateRobotCount + 1);
            cout << "Upgrading " << robotID() << " to " << newRobotID << endl;

            // Create a new UltimateRobot instance
            UltimateRobot* newRobot = new UltimateRobot(newRobotID, x, y);

            // Replace current MadBot in the battlefield
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
