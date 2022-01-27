#include "reader.h"
#include "stop.h"



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



