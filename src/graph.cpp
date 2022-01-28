// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#include "graph.h"
#include <queue>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1)
{
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight)
{
    if (src < 0 || src > n-1 || dest < 0 || dest > n-1)
        return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir)
        nodes[dest].adj.push_back({src, weight});
}

// ----------------------------------------------------------
// Exercicio 3: Algoritmo de Prim
// ----------------------------------------------------------
// TODO
int Graph::prim(int r)
{
    return 0;
}

// ----------------------------------------------------------
// Exercicio 5: Algoritmo de Kruskal
// ----------------------------------------------------------
// TODO
int Graph::kruskal()
{
    return 0;
}


void Graph::setStops(vector<Stop>& stops){
    this->stops = stops;
}
int Graph::getStopIndex(string& code){
    for(int i = 0 ; i< stops.size(); i++)
        if(stops[i].code == code)
            return i;
    
    cout << "Trying to Find "<< code << " That code does not exist!!\n";
    
    return -1;
}


void Graph::BFS(int startingNode)
{
    unordered_set<int> visitedNodes;
    queue<int> to_visitNodes;
    to_visitNodes.push(startingNode);
    visitedNodes.insert(startingNode);
    while (to_visitNodes.size())
    {
        int currentNode = to_visitNodes.front();
        to_visitNodes.pop();
        cout << stops[currentNode].code  << "->" ;
        //cout << nodes[currentNode].adj.size();
        
        for (Edge g : nodes[currentNode].adj)
        {
            if (visitedNodes.find(g.dest) == visitedNodes.end())
            {
                to_visitNodes.push(g.dest);
                visitedNodes.insert(g.dest);
            }   
        }
    }
}

void Graph::printAdjancies(int node){
   cout << stops[node].code << " Has connections to :\n";
   for(Edge e :nodes[node].adj){
       cout<< stops[e.dest].code << ", ";
   }

}
