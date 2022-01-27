#ifndef TRANSPORT_NETWORK_H
#define TRANSPORT_NETWORK_H

#include "graph.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class TransportNetwork
{

private:

    Graph* g;

public:

    TransportNetwork();

    void readStops(string& filename);
    void readLines(string& filename);
    int findStop(string& code) {return 0;};

    float distanceFunc (string& code1, string& code2) {return 0;};

};




#endif