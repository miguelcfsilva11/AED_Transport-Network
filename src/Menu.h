
#ifndef MENU_H
#define MENU_H


#include "transport_network.h"

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <set>

using namespace std;

struct choosingWay
{
    int howToChooseRoute;
    bool goOnFoot;
    int metresToWalk;
    unordered_set<string> hiddenLines;
    float startLat =0.0, endLat=0.0, startLong=0.0, endLong=0.0;
    string startStop=" ", endStop =" ";

};

/**
 * Class to make the Menu work
 */
class Menu
{

private:

    void showInfo();
    void chooseWay();
    TransportNetwork net;
    choosingWay CW;



public:
    
    Menu();
    void execute();
    void cleanScreen();
    int printMenu();

};


#endif