#ifndef CITY_H
#define CITY_H
#include <string>

class City
{
    public:
        City(std::string cityName, std::string countryName, float latitudeValue, float longitudeValue);
        ~City();
        std::string getCountry();
        std::string getCity();
        void setCountry(std::string newCountry);
        void setCity(std::string newCity);
        float getLongitude();
        float getLatitude();
        void setCoordinates(float newLatitude, float newLongitude);
        double distance(City &instance);
    protected:
    private:
        std::string city;
        std::string country;
        float longitude;
        float latitude;
};

#endif // CITY_H
