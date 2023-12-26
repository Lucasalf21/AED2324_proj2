#include "Airport.h"

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

bool Airport::operator<(const Airport &airport) const {
    return this->code < airport.code;
}
