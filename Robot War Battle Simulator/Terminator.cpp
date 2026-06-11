#include <iostream>
#include "Terminator.h"
#include "TerminatorRoboCop.h"

using namespace std;

int Terminator::incrementRobot_= 0;

    Terminator::Terminator(string robotID, int x, int y) : Robot(robotID, x, y)
    {
        incrementRobot_++;
    }

    Terminator::~Terminator() {}


    int Terminator::incrementRobot()
    {
        return incrementRobot_;
    }

    vector<pair<int, int>> Terminator::enemyPositions;

    void Terminator::setPosition(int x, int y)
    {
        setPositionX(x);
        setPositionY(y);
    }

    void Terminator::robotLook()
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
                        enemyPositions.push_back(make_pair(newX, newY));
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

    void Terminator::robotStep()
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
                for (auto& robot : *allRobots_)
                {
                    if (robot->robotID() == robotID_)
                    {
                        robot->setNumOfKills(numOfKills_);
                        break;
                    }
                }
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
        cout << robotID() << " moved to (" << newX << ", " << newY << ")." << endl;
    }

    void Terminator::actions()
    {
        robotLook();
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


    void Terminator::upgrade()
    {
        int terminatorRoboCopCount = 0;

        // Count existing TerminatorRoboCop
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

            // Replace current Terminator in the battlefield
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
                }*/
        }
    }
