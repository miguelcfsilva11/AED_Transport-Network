// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#include "graph.h"
#include <vector>
#include <algorithm>

bool Contains(const std::vector<int> &list, int x)
{
    return std::find(list.begin(), list.end(), x) != list.end();
}


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

vector<Stop>Graph::getStops()
{
    return stops;
}



int Graph::prim(int v) {
    vector<Node> alreadySeen;

    int totalWeight =0;
    int minWeight = 1000000000000;
    int d;
    alreadySeen.push_back(nodes[0]);

    for (int j=0; j<v; j++) {
        for (int i = 0; i < alreadySeen.size(); i++) {
            for (std::list<Edge>::iterator it = alreadySeen[i].adj.begin(); it != alreadySeen[i].adj.end(); it++)
            {
                if (it->weight <= minWeight && find(alreadySeen.begin(), alreadySeen.end(), nodes[it->dest]) == alreadySeen.end()) {
                    minWeight = it->weight;
                    d = it->dest;
                }

            }



        }
        alreadySeen.push_back(nodes[d - 1]);
        totalWeight = totalWeight + minWeight;
        minWeight = 1000000000;
    }

    return totalWeight;
}




vector<int> Graph::primPath(int v) {
    vector<Node> alreadySeen;
    vector<int> caminhos;
    int totalWeight =0;
    int minWeight = 1000000000000;
    int d;
    alreadySeen.push_back(nodes[0]);

    for (int j=0; j<v; j++) {
        for (int i = 0; i < alreadySeen.size(); i++) {
            for (std::list<Edge>::iterator it = alreadySeen[i].adj.begin(); it != alreadySeen[i].adj.end(); it++)
            {
                if (it->weight <= minWeight && find(alreadySeen.begin(), alreadySeen.end(), nodes[it->dest]) == alreadySeen.end()) {
                    minWeight = it->weight;
                    d = it->dest;
                }

            }



        }
        alreadySeen.push_back(nodes[d - 1]);
        caminhos.push_back(minWeight);
        totalWeight = totalWeight + minWeight;
        minWeight = 1000000000;
    }

    return caminhos;
}



// ----------------------------------------------------------
// Exercicio 5: Algoritmo de Kruskal
// ----------------------------------------------------------
// TODO
int Graph::kruskal() {
    return 0;
}
