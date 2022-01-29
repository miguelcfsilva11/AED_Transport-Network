#include <iostream>
#include <math.h>
#include "distance_calculator.h"

using namespace std;


float distanceFunc(GeoPoint g1,GeoPoint g2)
{
    int a, b;
    float lat1, lat2, long1, long2, distance;

    lat1 = g1.latitude; 
    long1 = g1.longitude;
    lat2 =  g2.latitude; 
    long2 = g2.longitude; 

    distance = 2*6371* asin(sqrt(pow(sin((lat2 - lat1) / 2), 2) + cos(lat1)* cos(lat2) *pow(sin((long2 - long1) / 2), 2)));
    if (distance < 0 )
        cout << "Oh NO !!!!!\n";
    return distance;
}

/*
int main(){


    //Paragem 1



    //Paragem dois

    cout << distanceFunc(p1,p2);


    return 0;
}
*/