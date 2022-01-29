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

        // cout << code << ", " << name << ", " << zone << ", " << latitude << ", " << longitude << endl;
        Stop stop = {code, name, zone, stof(latitude), stof(longitude)};
        stops.push_back(stop);
    }
    cout << "Read " << stops.size() << " stops!\n";
    g = new Graph(stops.size(), true);
    g->setStops(stops);
    cout << " Can create graph" << endl;
}

void TransportNetwork::readLines(std::string &filename, unordered_set<string> toExclude)
{

    cout << "Reading Lines!" << endl;
    std::ifstream in(filename);

    std::string dummy;
    std::string code;
    std::string name;
    int number_of_lines_read = 0;
    int number_of_unique_lines = 0;
    getline(in, dummy);
    while (getline(in, code, in.widen(',')))
    {
        if (toExclude.find(code) != toExclude.end())
            continue;

        getline(in, name, in.widen('\n'));

        string line_filename_0 = "../dataset/line_" + code + "_0.csv";
        string line_filename_1 = "../dataset/line_" + code + "_1.csv";
        // cout << "Reading Line Code :" << code << std::endl;
        // cout << "Reading Line Name:" << name << std::endl;

        // cout << "Sentido Normal!:\n";
        //  nao para se tiver empty lines
        readLine(line_filename_0, code);

        // cout << "Sentido Inverso!: \n";
        readLine(line_filename_1, code);
        number_of_lines_read += 2;
        number_of_unique_lines++;
    }
    cout << "Read in total : " << number_of_lines_read << " files\n";
    cout << "Read in total : " << number_of_unique_lines << " lines \n";
}

void TransportNetwork::readLine(string &line_filename, string &line_code)
{

    int next_stop_index;
    int current_stop_index;

    std::string current_stop, next_stop;
    std::ifstream line(line_filename);

    // cout << "Reading Line filename:" << line_filename << std::endl;
    // cout << "Current Stop     ||      Next Stop\n";
    // cout << "------------------------------------\n";
    // Reading the trash out
    getline(line, current_stop);
    // cout<< current_stop << " ";
    getline(line, current_stop);
    // cout<< current_stop << "\n";
    current_stop_index = g->getStopIndex(current_stop);
    if (current_stop_index == -1)
        return;

    // There's a case where some lines are empty apparently Such Has
    //  Trying to Find  That code does not exist!!
    //  ../dataset/line_300_1.csv
    //  Trying to Find  That code does not exist!!
    //  ../dataset/line_301_1.csv
    //  Trying to Find  That code does not exist!!
    //  ../dataset/line_302_1.csv
    //  Trying to Find  That code does not exist!!
    //  ../dataset/line_303_1.csv
    string trash;

    while (getline(line, next_stop) && next_stop != " " && next_stop != "\n")
    {
        // cout << current_stop << "            " << next_stop << std::endl;

        next_stop_index = g->getStopIndex(next_stop);
        g->getStops().at(next_stop_index).lines.insert(line_code);
        GeoPoint g1 = {g->getStops()[current_stop_index].latitude,g->getStops()[current_stop_index].longitude};
        GeoPoint g2 = {g->getStops()[next_stop_index].latitude,g->getStops()[next_stop_index].longitude};
        float distance  = calculateDistance(g1,g2);
        g->addEdge(current_stop_index, next_stop_index,distance);

        // Arrived
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
