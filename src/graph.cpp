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