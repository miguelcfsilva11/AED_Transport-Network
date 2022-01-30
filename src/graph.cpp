
#include "graph.h"
#include <queue>
#include <algorithm>
#include "distance_calculator.h"



Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1)
{
}


void Graph::addEdge(int src, int dest, float weight, string& line)
{
    if (src < 0 || src > n - 1 || dest < 0 || dest > n - 1)
        return;
    nodes[src].adj.push_back({dest, weight, 0, line});
    if (!hasDir)
        nodes[dest].adj.push_back({src, weight, 0, line});
}

void Graph::setStops(vector<Stop> &stops)
{
    this->stops = stops;
}

vector<Stop> &Graph::getStops()
{
    return this->stops;
}
int Graph::getStopIndex(string &code)
{
    for (int i = 0; i < stops.size(); i++)
        if (stops[i].code == code)
            return i;
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

    n³
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
pair<list<int>, float> Graph::dijkstraDistance(int origin, int chegada)
{

    GeoPoint originG  ={stops[origin].latitude,stops[origin].longitude};
    GeoPoint destinG  ={stops[chegada].latitude,stops[chegada].longitude};

    // Nodes that have been visited
    unordered_set<int> visitados;

    MinHeap<int, float> sorted_distances(n, n);
    unordered_map<int, float> node_distance_from_origin;
    unordered_map<int, int> anteriores;

    int MAX_DISTANCE = INT32_MAX;
    // Set all nodes at max Distance
    // At the begining all nodes are unreachable
    for (int i = 0; i < n; i++)
    {

        node_distance_from_origin[i] = MAX_DISTANCE;
        sorted_distances.insert(i, MAX_DISTANCE);
    }


    node_distance_from_origin[origin] = 0;
    sorted_distances.decreaseKey(origin, 0);


    int current;
    anteriores[current] =current;
    while (visitados.size() != n)
    {

        current = sorted_distances.removeMin();
        visitados.insert(current);

        for (Edge e : nodes[current].adj)
        {
            if (visitados.find(e.dest) == visitados.end() &&
                node_distance_from_origin[current] + e.weight < node_distance_from_origin[e.dest])
            {
                node_distance_from_origin[e.dest] = node_distance_from_origin[current] + e.weight;
                sorted_distances.decreaseKey(e.dest,node_distance_from_origin[current] + e.weight);
                anteriores[e.dest] = current;
            
                
            }
        }
    }

    list<int> caminho;
    int paragem_anterior;
    int paragem_corrente= chegada; 
    caminho.push_front(paragem_corrente);
    do{
        paragem_anterior = anteriores[paragem_corrente];
        caminho.push_front(paragem_anterior);
        paragem_corrente = paragem_anterior;
        
    }while(paragem_corrente != origin);
    

    return make_pair(caminho, node_distance_from_origin[chegada]);
}


pair<list<int>, float> Graph::minLinesDistance(int origin, int chegada, string currLine)
{

    GeoPoint originG  ={stops[origin].latitude,stops[origin].longitude};
    GeoPoint destinG  ={stops[chegada].latitude,stops[chegada].longitude};

    // Nodes that have been visited
    unordered_set<int> visitados;

    MinHeap<int, float> sorted_distances(n, n);
    unordered_map<int, float> node_distance_from_origin;
    unordered_map<int, int> anteriores;
    unordered_map<int, string> stopCurrLine;

    int MAX_DISTANCE = INT32_MAX;
    // Set all nodes at max Distance
    // At the begining all nodes are unreachable
    for (int i = 0; i < n; i++)
    {

        node_distance_from_origin[i] = MAX_DISTANCE;
        sorted_distances.insert(i, MAX_DISTANCE);
    }


    node_distance_from_origin[origin] = 0;
    sorted_distances.decreaseKey(origin, 0);

    stopCurrLine[origin] = currLine;


    int current;
    bool found = false;
    anteriores[current] =current;
    while (visitados.size() != n)
    {

        current = sorted_distances.removeMin();
        visitados.insert(current);

        for (Edge e : nodes[current].adj)
        {
            if (visitados.find(e.dest) == visitados.end())
            {
                if (e.line == stopCurrLine[current])
                {
                    if (node_distance_from_origin[e.dest] > node_distance_from_origin[current])
                    {
                        stopCurrLine[e.dest] = currLine;
                        node_distance_from_origin[e.dest] = node_distance_from_origin[current];
                        sorted_distances.decreaseKey(e.dest,node_distance_from_origin[current]);
                        anteriores[e.dest] = current;
                    }
                }

                else
                {
                    if (node_distance_from_origin[e.dest] > node_distance_from_origin[current] + 1)
                    {
                        stopCurrLine[e.dest] = e.line;
                        node_distance_from_origin[e.dest] = node_distance_from_origin[current] + 1;
                        sorted_distances.decreaseKey(e.dest,node_distance_from_origin[current] + 1);
                        anteriores[e.dest] = current;
                    }
                }
                
            }
        }
    }

    list<int> caminho;
    int paragem_anterior;
    int paragem_corrente= chegada; 
    float totalCost = 0;


    caminho.push_front(paragem_corrente);
    do{
        paragem_anterior = anteriores[paragem_corrente];
        caminho.push_front(paragem_anterior);
        
        GeoPoint g1 = {getStops()[paragem_anterior].latitude,getStops()[paragem_anterior].longitude};
        GeoPoint g2 = {getStops()[paragem_corrente].latitude,getStops()[paragem_corrente].longitude};
        
        totalCost += calculateDistance(g1, g2);
        paragem_corrente = paragem_anterior;

        
    }while(paragem_corrente != origin);

    return make_pair(caminho, totalCost);
}

pair<list<int>, float> Graph::minZonesDistance(int origin, int chegada)
{

    GeoPoint originG  ={stops[origin].latitude,stops[origin].longitude};
    GeoPoint destinG  ={stops[chegada].latitude,stops[chegada].longitude};


    unordered_set<int> visitados;

    MinHeap<int, float> sorted_distances(n, n);
    unordered_map<int, float> node_distance_from_origin;
    unordered_map<int, int> anteriores;

    int MAX_DISTANCE = INT32_MAX;
    // Set all nodes at max Distance
    // At the begining all nodes are unreachable
    for (int i = 0; i < n; i++)
    {

        node_distance_from_origin[i] = MAX_DISTANCE;
        sorted_distances.insert(i, MAX_DISTANCE);
    }


    node_distance_from_origin[origin] = 0;
    sorted_distances.decreaseKey(origin, 0);


    int current;
    anteriores[current] =current;
    while (visitados.size() != n)
    {

        current = sorted_distances.removeMin();
        visitados.insert(current);

        for (Edge e : nodes[current].adj)
        {
            if (visitados.find(e.dest) == visitados.end())
            {
                if (stops[e.dest].zone == stops[current].zone)
                {
                    if (node_distance_from_origin[e.dest] > node_distance_from_origin[current])
                    {
                        node_distance_from_origin[e.dest] = node_distance_from_origin[current];
                        sorted_distances.decreaseKey(e.dest,node_distance_from_origin[current]);
                        anteriores[e.dest] = current;
                    }
                }

                else
                    if (node_distance_from_origin[e.dest] > node_distance_from_origin[current] + 1)
                    {
                        node_distance_from_origin[e.dest] = node_distance_from_origin[current] + 1;
                        sorted_distances.decreaseKey(e.dest,node_distance_from_origin[current] + 1);
                        anteriores[e.dest] = current;
                    }
                
            }
        }
    }

    list<int> caminho;
    int paragem_anterior;
    int paragem_corrente= chegada; 
    caminho.push_front(paragem_corrente);
    do{
        paragem_anterior = anteriores[paragem_corrente];
        caminho.push_front(paragem_anterior);
        paragem_corrente = paragem_anterior;
        
    }while(paragem_corrente != origin);
    
    return make_pair(caminho, node_distance_from_origin[chegada]);
}




