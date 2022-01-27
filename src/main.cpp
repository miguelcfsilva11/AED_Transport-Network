#include "transport_network.h"


int main()
{  
    TransportNetwork net = TransportNetwork();

    string file_stops = "../dataset/stops.csv";
    string file_lines = "../dataset/lines.csv";

    net.readStops(file_stops);
    net.readLines(file_lines);
    
    return 0;
}