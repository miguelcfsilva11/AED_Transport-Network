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

    std::string dummy;
    std::string code;
    std::string name;

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


