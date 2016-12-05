#include "City.h"
#include <string>
#include <cmath>

#define PI 3.14159265

City::City(std::string cityName, std::string countryName, float latitudeValue, float longitudeValue) {
    city = cityName;
    country = countryName;
    latitude = latitudeValue;
    longitude = longitudeValue;
}
City::~City() {}
//-------------------------------GETTERS--------------------------
std::string City::getCity() {
    return city;
}
std::string City::getCountry() {
    return country;
}
float City::getLongitude() {
    return longitude;
}
float City::getLatitude() {
    return latitude;
}
//-------------------SETTERS------------------------------------
void City::setCoordinates(float newLatitude, float newLongitude) {
    latitude = newLatitude;
    longitude = newLongitude;
}
void City::setCity(std::string newCity) {
    city = newCity;
}
void City::setCountry(std::string newCountry) {
    country = newCountry;
}
double City::distance(City &instance) {
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = latitude * PI / 180;
    lon1r = longitude * PI / 180;
    lat2r = instance.getLatitude() * PI / 180;
    lon2r = instance.getLongitude() * PI / 180;
    u = sin((lat1r - lat2r)/2);
    v = sin((lon1r - lon2r)/2);
    return 2.0 * 6371 * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}
