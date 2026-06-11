#include <iostream>
#include "TerminatorRoboCop.h"
#include "UltimateRobot.h"
#include "Battlefield.h"

using namespace std;

int TerminatorRoboCop::incrementRobot_= 0;


    TerminatorRoboCop::TerminatorRoboCop(string robotID, int x, int y) : Robot(robotID, x, y)
    {
        incrementRobot_++;
    }


    int TerminatorRoboCop::incrementRobot()
    {
        return incrementRobot_;
    }

    vector<pair<int, int>> TerminatorRoboCop::enemyPositions;

    void TerminatorRoboCop::setPosition(int x, int y)
    {
        setPositionX(x);
        setPositionY(y);
    }

    void TerminatorRoboCop::robotLook()
    {
        bool foundEnemy = false;
        const int lookDistance = 1;
        const int startX = getX() - lookDistance;
        const int endX = getX() + lookDistance;
        const int startY = getY() - lookDistance;
        const int endY = getY() + lookDistance;

        for (int newX = startX; newX <= endX; ++newX)
        {
            for (int newY = startY; newY <= endY; ++newY)
            {
                // Skip the current position
                if (newX == getX() && newY == getY())
                    continue;

                // Check if the position is within the grid boundaries
                if (newX >= 0 && newX < gridCols && newY >= 0 && newY < gridRows)
                {
                    // Check if the position is occupied by another robot
                    if (!Robot::battlefield_[newY][newX].empty())
                    {
                        cout << "Enemy detected at (" << newX << ", " << newY << ")" << endl;
                        foundEnemy = true;
                        enemyPositions.push_back(make_pair(newX, newY));
                    }
                }
            }
        }

        if (!foundEnemy)
        {
            cout << "No enemies detected" << endl;
        }

    }

    void TerminatorRoboCop::robotShoot()
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
                cout << "TerminatorRoboCop fires at (" << targetX << ", " << targetY << ")." << endl;

                if(!Robot::battlefield_[targetY][targetX].empty())
                {
                    cout << "Enemy at (" << targetX << ", " << targetY << ") has been killed." << endl;
                    addDestroyedRobots(targetX, targetY);
                    numOfKills_++;
                    if (numOfKills_ == 3) {
                        upgrade(); // Check if upgrade is possible
                    }
                }

                shotsFired++;
            }
        }
    }

    void TerminatorRoboCop::robotStep()
    {
        int newX, newY;
        if (!enemyPositions.empty())
        {
            // Move towards the first enemy position stored in enemyPositions
            newX = enemyPositions[0].first;
            newY = enemyPositions[0].second;
            // Remove the enemy position from the list since we're moving towards it
            enemyPositions.clear();

            if (!Robot::battlefield_[newY][newX].empty())
            {
                cout << robotID() << " stepped on another robot and destroyed it." << endl;
                addDestroyedRobots(newX, newY);
                numOfKills_++;
            }
        }

        else
        {
            // If no enemy nearby, move to a random position
            do
            {
                newX = getX() + (rand() % 3) - 1;  // Generate random number between -1 and 1
                newY = getY() + (rand() % 3) - 1;
            } while ((newX == getX() && newY == getY()) || newX < 0 || newX >= gridCols || newY < 0 || newY >= gridRows);
        }

        // Clear the old position on the battlefield grid
        Robot::battlefield_[getY()][getX()] = "";

        setPositionX(newX);
        setPositionY(newY);

        Robot::battlefield_[newY][newX] = robotID_;
        cout << robotID() << " moved to (" << newX << ", " << newY << ")." << endl << endl;
    }

    void TerminatorRoboCop::actions()
    {
        robotLook();
        robotShoot();
        robotStep();

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

    void TerminatorRoboCop::upgrade()
    {
        int ultimateRobotCount = 0;

        // Count existing UltimateRobots
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
            string newRobotID = "UR0" + to_string(ultimateRobotCount + 1);
            cout << "Upgrading " << robotID() << " to " << newRobotID << endl;

            // Create a new UltimateRobot instance
            /*UltimateRobot* newRobot = new UltimateRobot(newRobotID, x, y);

            // Replace current TerminatorRoboCop in the battlefield
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


