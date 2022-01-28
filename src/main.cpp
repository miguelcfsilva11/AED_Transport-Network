#include "transport_network.h"


int main()
{  
    TransportNetwork net = TransportNetwork();

    string file_stops = "../dataset/stops.csv";
    string file_lines = "../dataset/lines.csv";
    unordered_set<string> toExclude ;
    toExclude.insert("1");

    net.readStops(file_stops);
    //cout << "Just Read Stops!! \n";
    net.readLines(file_lines,toExclude);
    //cout << "Just Read Lines!! \n";
    string stop;
    cin >> stop;
    int stop_index = net.getGraph()->getStopIndex(stop);
    if(stop_index != -1){
        cout << "Printing Adjancy list! :";
        net.getGraph()->printAdjancies(stop_index); 
    }

    return 0;
}