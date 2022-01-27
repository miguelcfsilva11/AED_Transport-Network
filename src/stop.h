#ifndef STOP_H
#define STOP_H

#include <string>
#include <unordered_set>

struct Stop{

    std::string code;
    std::string name;
    std::string zone;

    float latitude;
    float longitude;

    unordered_set<string> lines;


};

#endif