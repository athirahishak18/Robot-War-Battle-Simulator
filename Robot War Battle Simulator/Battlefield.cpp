#include <iostream>
#include <fstream>

#include "Battlefield.h"
#include "Robot.h"
#include "RoboCop.h"
#include "Terminator.h"
#include "TerminatorRoboCop.h"
#include "BlueThunder.h"
#include "MadBot.h"
#include "RoboTank.h"
#include "UltimateRobot.h"
using namespace std;



    Queue& Battlefield::getDestroyedRobots()
    {
        return destroyedRobots;
    }

    Battlefield::Battlefield()
    {
    }

    Battlefield::~Battlefield()
    {
        for (auto robot : robots_)
        {
            delete robot;
        }

    }

    int Battlefield::NUM_OF_COLUMN()
    {
        return NUM_OF_COLUMN_;
    }

    int Battlefield::NUM_OF_ROW()
    {
        return NUM_OF_ROW_;
    }

    int Battlefield::turns()
    {
        return turns_;
    }

    int Battlefield::numOfRobots()
    {
        return numOfRobots_;
    }

    vector<Robot*> Battlefield::robots()
    {
        return robots_;
    }

    vector<Robot*> Battlefield::allRobots()
    {
        return allRobots_;
    }

    vector<vector<string>> Battlefield::battlefield()
    {
        return battlefield_;
    }

    vector<Robot*>& Battlefield::getRobots()
    {
        return robots_;
    }

    vector<Robot*>& Battlefield::getAllRobots()
    {
        return allRobots_;
    }

    void Battlefield::readFile(string file)
    {
        string skipWord;
        string robotType = "";
        string robotName = "";
        string robotID = "";
        string positionX = "";
        string positionY = "";
        int x = -1;
        int y = -1;

        ifstream inFile;
        inFile.open(file);

        if(!inFile)
        {
            cout << "Error, cannot open " << file << endl;
            exit(1);
        }

        inFile >> skipWord;
        inFile >> skipWord;
        inFile >> skipWord;
        inFile >> NUM_OF_COLUMN_;
        inFile >> NUM_OF_ROW_;

        Robot::setGridDimensions(NUM_OF_COLUMN_, NUM_OF_ROW_);

        cout << "M by N: " << NUM_OF_COLUMN_ << " " << NUM_OF_ROW_ << "\n";
        inFile >> skipWord;
        inFile >> turns_;
        cout << "turns: " << turns_ << endl;
        inFile >> skipWord;
        inFile >> numOfRobots_;
        cout << "robots: " << numOfRobots_ << endl;

        for(int i=0; i < numOfRobots_; ++i)
        {
            inFile >> robotType;
            inFile >> robotName;
            inFile >> positionX;
            inFile >> positionY;
            cout << robotType << " " << robotName << " "<< positionX << " " << positionY << "\n";

            size_t underscorePosition = robotName.find('_');
            if(underscorePosition != string::npos)
            {
                robotID = robotName.substr(0, underscorePosition);
            }

            if(positionX == "random")
            {
                x = rand() % NUM_OF_COLUMN_;
                cout << robotID << " randomX: " << x << endl;
            }

            else
            {
                x = stoi(positionX);
            }

            if(positionY == "random")
            {
                y = rand() % NUM_OF_ROW_;
                cout << robotID << " randomY: " << y << endl;
            }

            else
            {
                y = stoi(positionY);
            }

            if(robotType == "RoboCop")
            {
                robots_.push_back(new RoboCop(robotID, x, y));
                allRobots_.push_back(new RoboCop(robotID, x, y));
            }

            else if(robotType == "Terminator")
            {
                robots_.push_back(new Terminator(robotID, x, y));
                allRobots_.push_back(new Terminator(robotID, x, y));
            }

            else if(robotType == "TerminatorRoboCop")
            {
                robots_.push_back(new TerminatorRoboCop(robotID, x, y));
                allRobots_.push_back(new TerminatorRoboCop(robotID, x, y));
            }

            else if(robotType == "BlueThunder")
            {
                robots_.push_back(new BlueThunder(robotID, x, y));
                allRobots_.push_back(new BlueThunder(robotID, x, y));
            }

            else if(robotType == "MadBot")
            {
                robots_.push_back(new MadBot(robotID, x, y));
                allRobots_.push_back(new MadBot(robotID, x, y));
            }

            else if(robotType == "RoboTank")
            {
                robots_.push_back(new RoboTank(robotID, x, y));
                allRobots_.push_back(new RoboTank(robotID, x, y));
            }

            else if(robotType == "UltimateRobot")
            {
                robots_.push_back(new UltimateRobot(robotID, x, y));
                allRobots_.push_back(new UltimateRobot(robotID, x, y));
            }
        }
        inFile.close();

        battlefield_.resize(NUM_OF_ROW_);
        for(int i = 0; i < battlefield_.size(); ++i)
        {
            battlefield_[i].resize(NUM_OF_COLUMN_);
        }

        for(int i = 0; i < battlefield_.size(); ++i)
        {
            for(int j = 0; j < battlefield_[i].size(); ++j)
            {
                battlefield_[i][j] = "";
            }
        }

        Robot::setRobots(&robots_);  // Set robots vector in Robot class
        Robot::setAllRobots(&allRobots_);  // Set robots vector in Robot class
        placeRobots();

        Robot::setBattlefield(battlefield_);
    }

    void Battlefield::placeRobots()
    {
        for(int i = 0; i<battlefield_.size(); ++i)
        {
            for(int j = 0; j<battlefield_[i].size(); ++j)
            {
                battlefield_[i][j] = "";
            }
        }

        for (int i = 0; i < robots_.size(); ++i)
        {
            if (robots_[i]->getY() < battlefield_.size() && robots_[i]->getX() < battlefield_[0].size())
            {
                battlefield_[robots_[i]->getY()][robots_[i]->getX()] = robots_[i]->robotID();
            }
            else
            {
            cout << "Error: Invalid location for the robot " << robots_[i]->robotID() << endl;
            exit(1);
            }
        }
    }

    void Battlefield::printRobots()
    {
        cout << "All Active Robots:" << endl;
        for (int i = 0; i < robots_.size(); ++i)
        {
            cout << "Robot ID: " << robots_[i]->robotID() << ", Position: (" << robots_[i]->getX() << ", " << robots_[i]->getY() << "), Lives: " << robots_[i]->numOfLives() << ", Kills: " << robots_[i]->numOfKills() << endl;
        }
        cout << endl;
    }

    void Battlefield::displayGrid() const
    {
        cout << "     ";
        for (int j = 0; j < battlefield_[0].size(); ++j)
        {
            cout << "  " << right << setfill('0') << setw(2) << j << " ";
        }
        cout << endl;

        for (int i = 0; i < battlefield_.size(); ++i)
        {
            cout << "    ";
            for (int j = 0; j < battlefield_[0].size(); ++j)
            {
                cout << "+----";
            }
            cout << "+" << endl;

            cout << "  " << right << setfill('0') << setw(2) << i;

            for (int j = 0; j < battlefield_[0].size(); ++j)
            {
                if(battlefield_[i][j] == "")
                {
                    cout << "|" << "    ";
                }

                else
                {
                    cout << "|" << left << setfill(' ') << setw(4) << battlefield_[i][j];
                }
            }
            cout << "|" << endl;
        }

        cout << "    ";
        for (int j = 0; j < battlefield_[0].size(); ++j)
        {
            cout << "+----";
        }

        cout << "+" << endl;
    }

    void Battlefield::robotActions()
    {

        static int i = 0;

        if (robots_.empty())
        {
            cout << "No robots available for actions." << endl;
            return;
        }

        if (robots_[i])
        {
        cout << *robots_[i] << " actions:  \n";
        robots_[i]->actions();
        cout << "\n";
        }

        else
        {
            cout << "Warning: Robot pointer is null." << endl;
        }

        i = (i + 1) % robots_.size();

        placeRobots(); // Update positions in battlefield after all actions
        printRobots();
    }

    void Battlefield::recoverRobot()
    {
        for (auto it = robots_.begin(); it != robots_.end(); ++it)
        {
            (*it)->recoverRobot();
        }
    }

    void Battlefield::outputFile(string filename) const
    {
        ofstream outFile(filename);

        if (!outFile)
        {
            cerr << "Error: Unable to open output file " << filename << endl;
            return;
        }

        // Write the battlefield grid to the file
        outFile << "Final Battlefield Grid:\n";
        outFile << "     ";
        for (int j = 0; j < battlefield_[0].size(); ++j)
        {
            outFile << "  " << right << setfill('0') << setw(2) << j << " ";
        }
        outFile << "\n";

        for (int i = 0; i < battlefield_.size(); ++i)
        {
            outFile << "    ";
            for (int j = 0; j < battlefield_[0].size(); ++j)
            {
                outFile << "+----";
            }
            outFile << "+" << "\n";

            outFile << "  " << right << setfill('0') << setw(2) << i;

            for (int j = 0; j < battlefield_[0].size(); ++j)
            {
                if (battlefield_[i][j] == "")
                {
                    outFile << "|" << "    ";
                }
                else
                {
                    outFile << "|" << left << setfill(' ') << setw(4) << battlefield_[i][j];
                }
            }
            outFile << "|" << "\n";
        }

        outFile << "    ";
        for (int j = 0; j < battlefield_[0].size(); ++j)
        {
            outFile << "+----";
        }
        outFile << "+" << "\n\n";

        // Write the details of all robots to the file
        outFile << "Active Robot Details:\n";
        for (int i = 0; i < robots_.size(); ++i)
        {
            outFile << "Robot ID: " << robots_[i]->robotID() << ", Position: (" << robots_[i]->getX() << ", " << robots_[i]->getY() << "), Lives: " << robots_[i]->numOfLives() << ", Kills: " << robots_[i]->numOfKills() << "\n";
        }

        outFile.close();
    }
