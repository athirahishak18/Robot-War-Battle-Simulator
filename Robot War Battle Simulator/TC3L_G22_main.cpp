// *********************************************************************************************************************
// Program: TC3L_G22_A1.cpp
// Course: CCP6124-OOPDS 
// Lecture Class: TC3L
// Tutorial Class: TT1L
// Trimester: 2510
// Student: 242UC2441U | Amalina      
// Student: 242UC244JW | Fatimah 
// Student: 242UC244V8 | Ezatul 
// Student: 242UC2441Z | Nur Athirah    
// *********************************************************************************************************************
// Task Distribution
// Member_1: Divided tasks accordingly, coded battlefield,
//           linked list, destruction of robots and recovering of robots.
// Member_2: In charge of the report, coded robot upgrade and linked list.
// Member_3: Implemented pseudocode and UML, coded queues,
//           destruction of robots and recovering of robots.
// Member_4: Acted as the leader and main programmer, fixed errors,
//           coded different robot classes and input/output to file.
// *********************************************************************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Battlefield.h"
#include "LinkedList.h"

using namespace std;

int main()
{
    srand(1221309435);

    Battlefield battlefield;
    LinkedList list;

    battlefield.readFile("fileInput1.txt");
    cout << endl;

    for(int i=0; i < battlefield.turns_; i++)
    {
        cout << "Turn " << i+1 << ":" << endl;
        battlefield.displayGrid();
        cout << "\n";
        battlefield.recoverRobot();
        battlefield.robotActions();

        if (battlefield.getRobots().size() <= 1)
        {
            cout << "Game over! Only one robot remains." << endl;
            break; // Exit the loop
        }
    }

    cout << "Final battlefield: " << endl;
    battlefield.displayGrid();

    Queue& destroyed = Robot::destroyedRobots;

    cout << "Destroyed Robots:" << endl;
    if (destroyed.empty())
    {
        cout << "No robots destroyed." << endl;
    }
    else
        {
        while (!destroyed.empty())
        {
            cout << destroyed.front() << endl;
            destroyed.pop();
        }
    }

    cout << endl;

    // Assuming you want to add all robots from Battlefield to LinkedList
    for (auto robot : battlefield.robots()) {
        list.addNode(robot->robotType(), robot->robotID(), robot->getX(), robot->getY());
    }

    list.printList();

    battlefield.outputFile("fileOutput1.txt");

    return 0;
}
