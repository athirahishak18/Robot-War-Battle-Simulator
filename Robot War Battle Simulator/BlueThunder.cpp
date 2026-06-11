#include <iostream>
#include "BlueThunder.h"
#include "MadBot.h"

using namespace std;

int BlueThunder::incrementRobot_= 0;

    BlueThunder::BlueThunder(string robotID, int x, int y) : Robot(robotID, x, y), currentShotIndex(0)
    {
        incrementRobot_++;
    }

    int BlueThunder::incrementRobot()
    {
        return incrementRobot_;
    }

    void BlueThunder::setPosition(int x, int y)
    {
        setPositionX(x);
        setPositionY(y);
    }

    void BlueThunder::robotShoot()
    {
        int dx[] = {0, 1, 1, 1, 0, -1, -1, -1}; // Change in X coordinate
        int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1}; // Change in Y coordinate

        // Get the current position of the robot
        int x = getX();
        int y = getY();

        // Calculate the target position to shoot at
        int targetX = x + dx[currentShotIndex];
        int targetY = y + dy[currentShotIndex];

        // Check if the target position is within the battlefield boundaries
        if (targetX >= 0 && targetX < gridCols && targetY >= 0 && targetY < gridRows && !(targetX == getX() && targetY == getY()))
        {
            // Shoot at the target position
            cout << "BlueThunder fires at (" << targetX << ", " << targetY << ")" << endl;

            // Check if there is an enemy robot at the target position
            if (!battlefield_[targetY][targetX].empty())
            {
                // Destroy the enemy robot
                cout << "Enemy at (" << targetX << ", " << targetY << ") has been destroyed." << endl;
                addDestroyedRobots(targetX, targetY);

                numOfKills_++;
            }
        }

        currentShotIndex = (currentShotIndex + 1) % 8; // Increment by 1 and wrap around to 0 after reaching 7
    }

    void BlueThunder::actions()
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

    void BlueThunder::upgrade()
    {
        int madBotCount = 0;

        for (auto robot : *robots_)
        {
            if (dynamic_cast<MadBot*>(robot) != nullptr)
            {
                madBotCount++;
            }
        }

        if (numOfKills_ == 3)
        {
            int x = getX();
            int y = getY();

            string currentRobot = robotID();

            // Create a new robot ID
            /*string newRobotID = "MB0" + to_string(madBotCount + 1);
            cout << "Upgrading " << robotID() << " to " << newRobotID << endl;

            // Create a new MadBot instance
            MadBot* newRobot = new MadBot(newRobotID, x, y);

            // Replace current BlueThunder in the battlefield
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
