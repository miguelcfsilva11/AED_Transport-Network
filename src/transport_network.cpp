#include "transport_network.h"

TransportNetwork::TransportNetwork()
{
    g = nullptr;
}

void TransportNetwork::readStops(string &filename)
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

        // cout << code << ", " << name << ", " << zone << ", " << latitude << ", " << longitude << endl;
        Stop stop = {code, name, zone, stof(latitude), stof(longitude)};
        stops.push_back(stop);
    }
    cout << "Read " << stops.size() << " stops!\n";
    g = new Graph(stops.size());
    g->getStops() = stops;
}

void TransportNetwork::readLines(std::string &filename)
{

    std::ifstream in(filename);

    std::string dummy;
    std::string code;
    std::string name;
    int number_of_lines_read = 0;
    int number_of_unique_lines =0;
    getline(in, dummy);
    while (getline(in, code, in.widen(',')))
    {
        getline(in, name, in.widen('\n'));

        string line_filename_0 = "../dataset/line_" + code + "_0.csv";
        string line_filename_1 = "../dataset/line_" + code + "_1.csv";
        //cout << "Reading Line Code :" << code << std::endl;
        //cout << "Reading Line Name:" << name << std::endl;
        // cout << "Previous Index"  <<  previous_index << std::endl;
        // cout << previous_stop << endl;

        //cout << "Sentido Normal!:\n";
        // nao para se tiver empty lines
        readLine(line_filename_0,code);

        //cout << "Sentido Inverso!: \n";
        readLine(line_filename_1,code);
        number_of_lines_read+=2; 
        number_of_unique_lines++;
    }
    cout << "Read in total : " << number_of_lines_read << " files\n";
    cout << "Read in total : " << number_of_unique_lines << " lines \n";
}

void TransportNetwork::readLine(string& line_filename,string& line_code){


    int next_stop_index;
    int current_stop_index;

    std::string current_stop, next_stop;
    std::ifstream line(line_filename);


    // cout << "Reading Line filename:" << line_filename << std::endl;
    // cout << "Current Stop     ||      Next Stop\n";
    // cout << "------------------------------------\n";

    while (getline(line, next_stop))
    {
        //cout << current_stop << "              " << next_stop << std::endl;
        next_stop_index = findStop(next_stop);
        g->addEdge(current_stop_index, next_stop_index, 1); // distanceFunc(previous_stop, curr_stop));
        // Arrived
        current_stop = next_stop;
    }

    g->getStops().at(findStop(current_stop)).lines.insert(line_code);
}