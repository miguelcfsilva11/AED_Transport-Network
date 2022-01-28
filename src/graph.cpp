// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#include "graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

void Graph::addStop(Stop& stop)
{
    stops.push_back(stop);
}

int Graph::findStop(Stop& stop)
{
    for (size_t i = 0; i < stops.size(); i++)
    {
        if (stop.code == stops[i].code)
            return i;
    }

    return -1;
}

vector<Stop>&Graph::getStops()
{
    return stops;
}
// ----------------------------------------------------------
// Exercicio 3: Algoritmo de Prim
// ----------------------------------------------------------
// TODO
int Graph::prim(int r) {
    return 0;
}


// ----------------------------------------------------------
// Exercicio 5: Algoritmo de Kruskal
// ----------------------------------------------------------
// TODO
int Graph::kruskal() {
    return 0;
}


pair<list<int>, float> Graph::dijkstraCostPath(int v, int k)
{

    unordered_map<int, float> distance;
    unordered_map<int, int> pred;

    MinHeap<int, float> priorityQueue = MinHeap<int,float>(n, n);

    for (int i = 1; i < nodes.size(); i++)
    {
        if (i == v) distance[i] = 0;
        else distance[i] = INT_MAX/2;
        priorityQueue.insert(i, distance[i]);
    }

    pred[v] = v;

    while(priorityQueue.getSize() != 0)
    {

        int curr_node = priorityQueue.removeMin();

        for(auto edge : nodes[curr_node].adj)
        {
            
            if (distance[edge.dest] > distance[curr_node] + edge.weight)
                distance[edge.dest] = distance[curr_node] + edge.weight;
                pred[edge.dest] = curr_node;
            
        }

    }

    list<int> dijkstraPath;
    float dijkstraCost = distance[k];
    int nextPred = k;

    dijkstraPath.insert(dijkstraPath.begin(), k);

    while (nextPred != v)
    {
        nextPred = pred[nextPred];
        dijkstraPath.insert(dijkstraPath.begin(), nextPred);
    }

    return make_pair(dijkstraPath, dijkstraCost);

}
