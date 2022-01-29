#ifndef TRANSPORT_NETWORK_H
#define TRANSPORT_NETWORK_H

#include "graph.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "distance_calculator.h"
class TransportNetwork
{

private:

    Graph* g;
public:
    vector<Stop> stops;

public:

    TransportNetwork();
    ~TransportNetwork();
    void readStops(string& filename);
    void readLines(string& filename,unordered_set<string> toExclude);
    void readLine(string& filename ,string& code);
    Graph * getGraph() ;

};

#endif