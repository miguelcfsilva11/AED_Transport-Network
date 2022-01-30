#ifndef TRANSPORT_NETWORK_H
#define TRANSPORT_NETWORK_H

#include "graph.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "distance_calculator.h"

/**
 * Class to store the network's graph and various useful methods
 */
class TransportNetwork
{

private:

    Graph* g;

public:

    /**
     * Constructor of the class TransportNetwork
     */
    TransportNetwork();

    /**
     * Destructor of the class TransportNetwork
     */
    ~TransportNetwork();

    /**
     * Function that reads the network's stops from a file
     * @param filename the file to read from
     */
    void readStops(string& filename);

    /**
     * Function that reads the network's lines from a file
     * @param filename the file to read from
     * @param toExclude unordered set with the codes of the lines to be excluded
     * @param nightTime true if it is possible to select nocturnal or diurnal travels, false otherwise
     */
    void readLines(string& filename,unordered_set<string> toExclude, bool nightTime);

    /**
     * Function that reads a line from a file
     * @param filename the file to read from
     * @param code the code of a stop
     */
    void readLine(string& filename ,string& code);

    /**
     * Function that returns the used graph
     * @return returns the used graph
     */
    Graph * getGraph() ;

};

#endif