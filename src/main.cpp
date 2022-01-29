#include "transport_network.h"
#include "Menu.h"

int main()
{

    TransportNetwork net = TransportNetwork();

    //Menu menu = Menu();
    
    
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

    for (auto line : net.getGraph()->getStops()[stop1_index].lines)
    {
        cout << line << endl;
    }
    
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

        float cost, min_cost = INT_MAX/2;
        for (auto line: g->getStops()[stop1_index].lines)
        {
            cost = g->minLinesDistance(stop1_index,stop2_index, line).second;
            if (cost < min_cost)
                min_cost = cost;
        }


        for(int i = 0 ; i < 50; i++)
        {
            cout << '\n';
        }

        cout << cost << endl;
    }



    return 0;
}