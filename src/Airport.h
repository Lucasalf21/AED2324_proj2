#ifndef AED2324_PROJ2_AIRPORT_H
#define AED2324_PROJ2_AIRPORT_H

#include <string>

using namespace std;

class Airport {
private:
    string code;
    string name;
    string city;
    string country;
    pair<float, float> coordinates;
    int numFlights = 0;
public:
    Airport();
    explicit Airport(string code, string name = "", string city = "", string country = "", float latitude = 0, float longitude = 0);
    string getCode();
    string getName();
    string getCity();
    string getCountry();
    int getNumFlights() const;
    float getLatitude() const;
    float getLongitude() const;
    double calculateDistance(Airport* dest);
    bool operator <(const Airport& airport) const;
    bool operator =(const Airport& airport);

    void addFlight();
};


#endif //AED2324_PROJ2_AIRPORT_H
