#include "transport_network.h"


int main()
{  
    TransportNetwork net = TransportNetwork();

    string file_stops = "../dataset/stops.csv";
    string file_lines = "../dataset/lines.csv";

    net.readStops(file_stops);
    cout << "Just Read Stops!! \n";
    net.readLines(file_lines);
    cout << "Just Read Lines!! \n";
    
    return 0;
}