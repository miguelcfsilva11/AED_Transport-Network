
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

using std::vector, std::string;

struct choosingWay
{
    int howToChooseRoute;
    bool goOnFoot;
    int metresToWalk;
    vector<string> hiddenLines;
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
    choosingWay chooseWay();



public:
    choosingWay printMenu();
    Menu();

};


#endif