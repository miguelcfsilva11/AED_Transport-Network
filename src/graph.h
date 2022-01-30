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
        string line;

        bool operator<(const Edge& edge) const
        {
            return weight > edge.weight;
        }

    };

    struct Node {
        list<Edge> adj;     //The list of outgoing edges (to adjacent nodes)

    };


    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes;
    vector<Stop> stops;

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, float weight, string& line);

    // ----- Functions to implement in this class -----
    int prim(int v);
    vector<int> primPath(int v);
    int kruskal();

    vector<Stop>& getStops();
    void setStops(vector<Stop>& stop);
    int getStopIndex(string &stop_code);
    void printAdjancies(int node );
    void addYourLocation(float starLat, float endLat , float maxDistance = 200000);
    pair<list<int>, int> BFS(int partida, int chegada);
    pair<list<int>, float> primDistance(int partida, string zone);
    pair<list<int>, float> dijkstraDistance(int partida, int chegada);
    pair<list<int>, float> minLinesDistance(int partida, int chegada, string line);
    pair<list<int>, float> minZonesDistance(int partida, int chegada);


};


#endif