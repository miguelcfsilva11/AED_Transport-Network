#include <math.h>


/**
 * Struct to store the latitude and longitude of a certain place on Earth
 */
struct GeoPoint{
    float latitude;
    float longitude;
};


/**
* Function to calculate the distance between two places using the Haversine formula
* @param g1 the first place
* @param g2 the second place
* @return returns the distance between the two places
*/
float calculateDistance(GeoPoint g1,GeoPoint g2);