
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "minHeap.h"
#include "disjointSets.h"
#include "stop.h"
#include <vector>
#include <list>
#include <iostream>
#include <climits>

using namespace std;

/**
 * Class to store the graph's edges, nodes, size, vector of nodes, vector of stops and indication about if the graph is undirected or not
 */
class Graph {

    /**
     * Struct to store the edges destination node, weight, line and if it can be reached by foot
     */
    struct Edge {

        int dest;   //Destination node
        float weight; //An integer weight
        string line;

        bool operator<(const Edge& edge) const
        {
            return weight > edge.weight;
        }

    };

    /**
     * Struct to store the node's list of outgoing edges to adjacent nodes
     */
    struct Node {
        list<Edge> adj;     //The list of outgoing edges (to adjacent nodes)

    };


    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes;
    vector<Stop> stops;

public:


    /**
     * Constructor of the class Graph
     * @param nodes number of nodes
     * @param dir false if the graph is undirected (default), true otherwise
     */
    Graph(int nodes, bool dir = false);

    /**
     * Function to add an edge from source to destination with a certain weight
     * @param src the source
     * @param dest the destination
     * @param weight the weight
     * @param line the line
     */
    void addEdge(int src, int dest, float weight, string& line);

    /**
     * Function that implements the Prim algorithm to find a MST and the minimal total weight
     * @param v number of nodes in the graph
     * @return returns the minimal total weight (the weight of the MST)
     */
    int prim(int v);

    /**
     * Function that implements the Prim algorithm to find a MST
     * @param v number of nodes in the graph
     * @return returns a vector with the nodes of the MST
     */
    vector<int> primPath(int v);


    /**
     * Function that implements the BFS algorithm
     * @param startingNode the node where it starts
     */
    void BFS(int startingNode);

    /**
     * Function that returns the graph's vector of stops
     * @return returns the graph's vector of stops
     */

    vector<Stop>& getStops();

    /**
     * Function that sets the graph's vector of stops to stops
     * @param stops the new vector of stops
     */
    void setStops(vector<Stop>& stops);

    /**
     * Function that searchs for a code in the graph's vector of stops and returns its index
     * @param code the code to be searched
     * @return returns the index of the stop with the given code in the vector of stops
     */
    int getStopIndex(string &code);

    /**
     * Function that prints a node's adjacent nodes
     * @param node the node whose adjacent nodes are to be printed
     */
    void printAdjancies(int node );

    /**
     * @brief Adds your current location to the graph with edges connecting to the nodes with the distance 
     * between  them are lesser then maxDistance.
     * 
     * @param starLat  Your Current Location Latitude
     * @param endLat Your Current Location longitude
     * @param maxDistance  The maxDistance you want to walk
     */
    void addYourLocation(float starLat, float endLat , float maxDistance = 200000);

    /**
     * @brief  A Breadth First Search starting in node partida and ending in chegada
     * that returns the path to the node
     * 
     * @param partida  starting node
     * @param chegada   ending node  
     * @return pair<list<int>, int>  the path and the number to the ending node the number of stops in the returned path
     */
    pair<list<int>, int> BFS(int partida, int chegada);
    /**
     * @brief Returns the minimum cost path to traverse an entire zone starting at the given node
     * 
     * @param partida the starting node
     * @param zone  the zone to be traversed
     * @return pair<list<int>, float>  the path and the total distance traversed
     */
    pair<list<int>, float> primDistance(int partida, string zone);

    /**
     * @brief The  shortest path between two nodes doens't care if zone or lines change
     * 
     * @param partida  starting node
     * @param chegada  ending node
     */
    pair<list<int>, float> dijkstraDistance(int partida, int chegada);

    /**
     * @brief The shortest path between two nodes prioritizing not changing lines.
     * 
     * @param partida  starting node
     * @param chegada  ending node
     * @param line  the starting line
     * @return pair<list<int>, float>  a  pair with the path and the total distance traversed
     */
    pair<list<int>, float> minLinesDistance(int partida, int chegada, string line);
    /**
     * @brief The shortest path between two nodes prioritizing not changing zones.
     * 
     * @param partida  starting node
     * @param chegada  ending node
     * @return pair<list<int>, float>  a  pair with the path and the total distance traversed
     */
    pair<list<int>, float> minZonesDistance(int partida, int chegada);

};

#endif