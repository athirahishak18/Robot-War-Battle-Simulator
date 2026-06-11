#include <iostream>
#include "UltimateRobot.h"

using namespace std;

int UltimateRobot::incrementRobot_= 0;

    UltimateRobot::UltimateRobot(string robotID, int x, int y) : Robot(robotID, x, y)
    {
       incrementRobot_++;
    }

    int UltimateRobot::incrementRobot()
    {
        return incrementRobot_;
    }

    vector<pair<int, int>> UltimateRobot::enemyPositions;

    void UltimateRobot::setPosition(int x, int y)
    {
        setPositionX(x);
        setPositionY(y);
    }

    void UltimateRobot::robotLook()
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

    void UltimateRobot::robotShoot()
    {
        const int NUM_SHOTS = 4;
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
                cout << "UltimateRobot fires at (" << deltaX << ", " << deltaY << ")." << endl;

                if(!Robot::battlefield_[deltaY][deltaX].empty())
                {
                    cout << "Enemy at (" << deltaX << ", " << deltaY << ") has been killed." << endl;
                    addDestroyedRobots(deltaX, deltaY);
                }
                shotsFired++;
            }
        }
    }

    void UltimateRobot::robotStep()
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

    void UltimateRobot::actions()
    {
        robotLook();
        robotShoot();
        robotStep();

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
