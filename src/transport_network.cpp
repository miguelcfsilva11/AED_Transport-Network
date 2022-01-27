#include "transport_network.h"

TransportNetwork::TransportNetwork()
{
    g = nullptr;
}

void TransportNetwork::readStops(string& filename)
{

    std::vector<Stop> stops;

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

        //cout << code << ", " << name << ", " << zone << ", " << latitude << ", " << longitude << endl;
        Stop stop = {code, name, zone, stof(latitude), stof(longitude)};
        stops.push_back(stop);

    }


    g = new Graph(stops.size());
    g->getStops() = stops;

}


void TransportNetwork::readLines(std::string& filename)
{

    std::ifstream in(filename);
    std::ifstream line;

    std::string dummy;
    std::string code;
    std::string name;

    int previous_index;
    int curr_index;


    std::string curr_stop, previous_stop;

    getline(in, dummy);

    while (in)
    {

        getline(in, code, in.widen(','));
        getline(in, name, in.widen('\n'));


        line.open("../dataset/line_" + code + "_0.csv");
        getline(line, dummy, '\n');
        getline(line, previous_stop, '\n');

        previous_index = findStop(previous_stop); 
        cout << previous_stop << endl;
        while (line.peek() != EOF)
        {
            
            getline(line, curr_stop, '\n');
            cout << curr_stop << ", " << previous_stop << endl;
            curr_index = findStop(curr_stop);
            g->addEdge(previous_index, curr_index, 1);//distanceFunc(previous_stop, curr_stop));

            curr_stop = previous_stop;
        }

        g->getStops().at(findStop(curr_stop)).lines.insert(code);

    }




}
