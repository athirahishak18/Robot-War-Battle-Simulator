#include <iostream>
#include "MadBot.h"
#include "RoboTank.h"

using namespace std;

int MadBot::incrementRobot_= 0;

    MadBot::MadBot(string robotID, int x, int y) : Robot(robotID, x, y)
    {
        incrementRobot_++;
    }

    int MadBot::incrementRobot()
    {
        return incrementRobot_;
    }

    void MadBot::setPosition(int x, int y)
    {
        setPositionX(x);
        setPositionY(y);
    }

    void MadBot::robotShoot()
    {
        const int NUM_SHOTS = 1;
        int shotsFired = 0;

        while (shotsFired < NUM_SHOTS)
        {
            int deltaX = (rand() % 3) - 1;
            int deltaY = (rand() % 3) - 1;
            int targetX = getX() + deltaX;
            int targetY = getY() + deltaY;

            if (targetX >= 0 && targetX < gridCols && targetY >= 0 && targetY < gridRows && !(targetX == getX() && targetY == getY()))
            {
                cout << "MadBot fires at (" << targetX << ", " << targetY << ")." << endl;

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

    void MadBot::actions()
    {
        robotShoot();

        if (numOfKills_ == 3 && !upgraded_)
        {
            upgrade(); // Check if upgrade is possible
            upgraded_ = true; // Mark as upgraded
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

    void MadBot::upgrade()
    {
        int roboTankCount = 0;

        // Count existing RoboTank
        for (auto robot : *robots_)
        {
            if (dynamic_cast<RoboTank*>(robot) != nullptr)
            {
                roboTankCount++;
            }
        }

        if (numOfKills_ == 3)
        {
            int x = getX();
            int y = getY();

            string currentRobot = robotID();

            // Create a new robot ID
            string newRobotID = "RT0" + to_string(roboTankCount + 1);
            cout << "Upgrading " << robotID() << " to " << newRobotID << endl;

            // Create a new RoboTank instance
            /*RoboTank* newRobot = new RoboTank(newRobotID, x, y);

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
