#include "Airport.h"
#include <cmath>
#include <utility>

Airport::Airport(string code, string name, string city, string country, float latitude, float longitude) {
    this->code = std::move(code);
    this->name = std::move(name);
    this->city = std::move(city);
    this->country = std::move(country);
    this->coordinates = make_pair(latitude, longitude);
}

string Airport::getCode() {
    return code;
}

string Airport::getName() {
    return name;
}

string Airport::getCity() {
    return city;
}

string Airport::getCountry() {
    return country;
}

float Airport::getLatitude() const {
    return coordinates.first;
}

float Airport::getLongitude() const {
    return coordinates.second;
}

Airport::Airport() {    // default constructor
    this->code = "";
    this->name = "";
    this->city = "";
    this->country = "";
    this->coordinates = make_pair(0, 0);
}

double Airport::calculateDistance(Airport* dest){
    const double earthRadius = 6371.0;

    double lat1 = this->getLatitude() * (M_PI / 180.0);
    double long1 = this->getLongitude() * (M_PI / 180.0);
    double lat2 = dest->getLatitude() * (M_PI / 180.0);
    double long2 = dest->getLongitude() * (M_PI / 180.0);

    double dlat = lat2 - lat1;
    double dlong = long2 - long1;

    double a = sin(dlat / 2.0) * sin(dlat / 2.0) + cos(lat1) * cos(lat2) * sin(dlong / 2.0) * sin(dlong / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

    return earthRadius * c;
}

bool Airport::operator<(const Airport &airport) const {
    return this->code < airport.code;
}

bool Airport::operator=(const Airport &airport) {
    return this->code == airport.code;
}