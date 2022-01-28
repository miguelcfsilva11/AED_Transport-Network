// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

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

class Graph {
    
    struct Edge {
        int dest;   //Destination node
        float weight; //An integer weight
        bool byFoot;
    };

    struct Node {

        list<Edge> adj;     //The list of outgoing edges (to adjacent nodes)

    };


    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes;
    vector<Stop> stops; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int weight = 1);
    void addStop(Stop& stop);

    int findStop(Stop& stop);

    vector<Stop>& getStops();

    // ----- Functions to implement in this class -----
    int prim(int v);
    int kruskal();
    pair<list<int>, float> dijkstraCostPath(int v, int k);
};

#endif
