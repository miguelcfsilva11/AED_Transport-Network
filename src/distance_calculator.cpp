#include <iostream>
#include <math.h>
#include "distance_calculator.h"

using namespace std;


float calculateDistance(GeoPoint g1, GeoPoint g2)
{
    float lat1, lat2, long1, long2, distance;

    lat1 = g1.latitude;
    long1 = g1.longitude;
    lat2 = g2.latitude;
    long2 = g2.longitude;

    if (distance < 0)
        cout << "Oh NO !!!!!\n";

    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (long2 - long1) * M_PI / 180.0;


    lat1 = (lat1)*M_PI / 180.0;
    lat2 = (lat2)*M_PI / 180.0;


    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
    return distance;
}