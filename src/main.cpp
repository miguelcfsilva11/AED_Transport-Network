#include "transport_network.h"
#include "Menu.h"

int main()
{

    TransportNetwork net = TransportNetwork();

    // Menu menu = Menu();
    
    
    string file_stops = "../dataset/stops.csv";
    string file_lines = "../dataset/lines.csv";
    unordered_set<string> toExclude;
    net.readStops(file_stops);
    net.readLines(file_lines, toExclude);
    string stop1;
    string stop2;
    cout << " Primeira Paragem : ";
    cin >> stop1;
    cout << "\n Segunda Paragem : ";
    cin >> stop2;
    int stop1_index = net.getGraph()->getStopIndex(stop1);
    int stop2_index = net.getGraph()->getStopIndex(stop2);
    
    auto g = net.getGraph();
    if (stop1_index != -1 && stop2_index != -1)
    {
        /*
        auto c = g->shortestCostPath(stop1_index, stop2_index);
        cout << "O caminho obtido :\n ";
        for (int i : c.first)
        {
            cout << g->getStops()[i].code  << " -> " ;
    
        }
        */
        cout << "Resultado dijkstra : " << g->dijkstraDistance(stop1_index,stop2_index) << endl;

    }



    return 0;
}