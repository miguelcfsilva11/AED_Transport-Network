// AED 2021/2022 - Aula Pratica 10
// Pedro Ribeiro (DCC/FCUP) [09/01/2022]

#include "graph.h"
#include <queue>
#include <algorithm>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1)
{
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, float weight)
{
    if (src < 0 || src > n - 1 || dest < 0 || dest > n - 1)
        return;
    nodes[src].adj.push_back({dest, weight,0});
    if (!hasDir)
        nodes[dest].adj.push_back({src, weight,0});
}

void Graph::setStops(vector<Stop> &stops)
{
    this->stops = stops;
}
int Graph::getStopIndex(string &code)
{
    for (int i = 0; i < stops.size(); i++)
        if (stops[i].code == code)
            return i;

    cout << "Trying to Find " << code << " That code does not exist!!\n";

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
        cout << stops[currentNode].code << "->";
        // cout << nodes[currentNode].adj.size();

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

void Graph::printAdjancies(int node)
{
    cout << stops[node].code << " Has connections to :\n";
    for (Edge e : nodes[node].adj)
    {
        cout << stops[e.dest].code << ", ";
    }
}
/*
int Graph::prim(int v)
{
    vector<Node> alreadySeen;

    int totalWeight = 0;
    int minWeight = INT32_MAX;
    int d;
    alreadySeen.push_back(nodes[0]);

    for (int j = 0; j < v; j++)
    {
        for (int i = 0; i < alreadySeen.size(); i++)
        {
            for (std::list<Edge>::const_iterator it = alreadySeen[i].adj.begin(); it != alreadySeen[i].adj.end(); it++)
            {
                if (it->weight <= minWeight && find(alreadySeen.begin(), alreadySeen.end(), nodes[it->dest]) == alreadySeen.end())
                {
                    minWeight = it->weight;
                    d = it->dest;
                }
            }
        }
        alreadySeen.push_back(nodes[d - 1]);
        totalWeight = totalWeight + minWeight;
        minWeight = INT32_MAX;
    }

    return totalWeight;
}
vector<int> Graph::primPath(int v)
{
    vector<Node> alreadySeen;
    vector<int> caminhos;
    int totalWeight = 0;
    int minWeight = INT32_MAX;
    int d;
    alreadySeen.push_back(nodes[0]);

    for (int j = 0; j < v; j++)
    {
        for (int i = 0; i < alreadySeen.size(); i++)
        {
            for (std::list<Edge>::const_iterator it = alreadySeen[i].adj.begin(); it != alreadySeen[i].adj.end(); it++)
            {
                if (it->weight <= minWeight && find(alreadySeen.begin(), alreadySeen.end(), nodes[it->dest]) == alreadySeen.end())
                {
                    minWeight = it->weight;
                    d = it->dest;
                }
            }
        }
        alreadySeen.push_back(nodes[d - 1]);
        caminhos.push_back(minWeight);
        totalWeight = totalWeight + minWeight;
        minWeight = INT32_MAX;
    }

    return caminhos;
}
*/

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
