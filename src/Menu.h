
#ifndef MENU_H
#define MENU_H


#include "transport_network.h"

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <set>

using namespace std;

/**
 * Struct to store various aspects of the users decision when interacting with the menu
 */
struct choosingWay
{
    int howToChooseRoute;
    bool goOnFoot;
    bool nightTime;
    int metresToWalk;
    unordered_set<string> hiddenLines;
    float startLat =0.0, endLat=0.0, startLong=0.0, endLong=0.0;
    string startStop=" ", endStop =" ";

};

/**
 * Class with methods that will make the Menu work
 */
class Menu
{

private:

    /**
     * Function that prints a certain message on the screen
     */
    void showInfo();

    /**
     * Function thar gathers various aspects of the users decisions refarding various questions
     */
    void chooseWay();

    TransportNetwork net;
    choosingWay CW;



public:

    /**
     * Constructor of the class Menu
     */
    Menu();

    /**
     * Function to choose the right path according to the user's decisions
     */
    void execute();

    /**
     * Function to "clean the screen"
     */
    void cleanScreen();

    /**
     * Function that prints the Menu
     * @return returns the decicion of the user regarding the questions shown in the Menu
     */
    int printMenu();

};


#endif