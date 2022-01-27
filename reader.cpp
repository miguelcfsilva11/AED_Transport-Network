#include "reader.h"

void readStops(std::string& filename)
{

    std::vector<Stop> stops;

    std::ifstream in(filename);

    std::string dummy;

    std::string code;
    std::string name;
    std::string zone;
    std::string latitude;
    std::string longitude;

    int counter = 0;

    while (counter < 5)
    {
        getline(in, dummy,in.widen(','));
        counter++;
    }

    counter = 0;

    while (in)
    {

        getline(in, code, in.widen(','));
        getline(in, name, in.widen(','));
        getline(in, zone, in.widen(','));
        getline(in, latitude, in.widen(','));
        getline(in, longitude, in.widen(','));

        Stop stop = {code, name, zone, stof(latitude), stof(longitude)};
        stops.push_back(stop);
    }


}



void readLines(std::string& filename)
{

    std::vector<Line> lines;

    std::ifstream in(filename);
    std::ifstream line;

    std::string dummy;
    std::string code;
    std::string name;

    int previous_index;
    int curr_index;


    std::string curr_stop, previous_stop;

    int counter = 0;

    while (counter < 2)
    {
        getline(in, dummy,in.widen(','));
        counter++;
    }

    counter = 0;

    while (in)
    {

        getline(in, code, in.widen(','));
        getline(in, name, in.widen(','));


        line.open("line_file");
        getline(in, dummy);
        getline(in, previous_stop); //bb13
        previous_index = stops.find(previous_stop) //bb13
        
        while (line)
        {
            
            getline(in, curr_stop);
            curr_index = stops.find(curr_stop);
            

            g.addEdge(previous_index, curr_index, distanceFunc(previous_stop, stop_code))
        

        }

        Line line = {code, name};
        lines.push_back(line);
    }


}



struct Stop{

    std::string code;
    std::string name;
    std::string zone;

    float latitude;
    float longitude;

};

struct Line{

    std::string code;
    std::string name;
};