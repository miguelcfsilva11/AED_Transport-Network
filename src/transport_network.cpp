#include "transport_network.h"
#include <math.h>
TransportNetwork::TransportNetwork()
{
    g = nullptr;
}

void TransportNetwork::readStops(string &filename)
{
    vector<Stop> stops;
    std::ifstream in(filename);

    std::string dummy;

    std::string code;
    std::string name;
    std::string zone;
    std::string latitude;
    std::string longitude;

    getline(in, dummy);

    while (in.peek() != EOF)
    {

        getline(in, code, in.widen(','));
        getline(in, name, in.widen(','));
        getline(in, zone, in.widen(','));
        getline(in, latitude, in.widen(','));
        getline(in, longitude, in.widen('\n'));

        Stop stop = {code, name, zone, stof(latitude), stof(longitude)};
        stops.push_back(stop);
    }

    g = new Graph(stops.size(), true);
    g->setStops(stops);

}

void TransportNetwork::readLines(std::string &filename, unordered_set<string> toExclude, bool nightTime)
{


    std::ifstream in(filename);

    std::string dummy;
    std::string code;
    std::string name;

    bool nocturnal = false;

    int number_of_lines_read = 0;
    int number_of_unique_lines = 0;
    getline(in, dummy);

    while (getline(in, code, in.widen(',')))
    {
        if (toExclude.find(code) != toExclude.end())
            continue;


        getline(in, name, in.widen('\n'));
    
        for (size_t i = 0; i < code.size(); i++)
        {
            if (code[i] == 'M')
            {
                nocturnal = true;
            }
        }

        string line_filename_0 = "../dataset/line_" + code + "_0.csv";
        string line_filename_1 = "../dataset/line_" + code + "_1.csv";

        if (nightTime == nocturnal)
        {

            readLine(line_filename_0, code);
            readLine(line_filename_1, code);

            number_of_lines_read += 2;
            number_of_unique_lines++;
        }   

        nocturnal = false;
    }
}

void TransportNetwork::readLine(string &line_filename, string &line_code)
{

    int next_stop_index;
    int current_stop_index;

    std::string current_stop, next_stop;
    std::ifstream line(line_filename);


    getline(line, current_stop);
    getline(line, current_stop);

    current_stop_index = g->getStopIndex(current_stop);
    if (current_stop_index == -1)
        return;

    string trash;

    while (getline(line, next_stop) && next_stop != " " && next_stop != "\n")
    {


        next_stop_index = g->getStopIndex(next_stop);
        g->getStops().at(next_stop_index).lines.insert(line_code);

        GeoPoint g1 = {g->getStops()[current_stop_index].latitude,g->getStops()[current_stop_index].longitude};
        GeoPoint g2 = {g->getStops()[next_stop_index].latitude,g->getStops()[next_stop_index].longitude};
        float distance  = calculateDistance(g1,g2);

        g->addEdge(current_stop_index, next_stop_index, distance, line_filename);
        current_stop = next_stop;
        current_stop_index = next_stop_index;
    }
}

Graph *TransportNetwork::getGraph()
{
    return g;
}

TransportNetwork::~TransportNetwork()
{
    delete g;
    cout << "No more memory leaks hopefully " << endl;
}
