//
// Created by Gonçalo Carvalho on 26/12/2023.
//

#include "Airline.h"

#include <utility>

Airline::Airline(string code, string name, string callsign, string country) {
    this->code = std::move(code);
    this->name = std::move(name);
    this->callsign = std::move(callsign);
    this->country = std::move(country);
}

string Airline::getCode() {
    return code;
}

string Airline::getName() {
    return name;
}

string Airline::getCallsign() {
    return callsign;
}

string Airline::getCountry() {
    return country;
}

Airline::Airline() {    // default constructor
    this->code = "";
    this->name = "";
    this->callsign = "";
    this->country = "";
}
