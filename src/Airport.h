//
// Created by Gonçalo Carvalho on 26/12/2023.
//

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
public:
    Airport();
    Airport(string code, string name, string city, string country, float latitude, float longitude);
    string getCode();
    string getName();
    string getCity();
    string getCountry();
    float getLatitude() const;
    float getLongitude() const;
};


#endif //AED2324_PROJ2_AIRPORT_H
