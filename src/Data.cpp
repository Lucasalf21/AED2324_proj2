#include "Data.h"

Data::Data() {
}

void Data::newAirport(Airport* airport) {
    airports.insert(airport);
}

void Data::newAirline(Airline* airline) {
    airlines.insert(airline);
}

void Data::newFlight(Flight *flight) {
    flights.insert(flight);
}

Airport *Data::getAirport(string code) {
    for(auto airport : airports) {
        if(airport->getCode() == code) {
            return airport;
        }
    }
    return nullptr;
}

Airport* Data::getAirportByCity(const string& city) const {
    for (auto airport : airports) {
        if (airport->getCity() == city) {
            return airport;
        }
    }
    return nullptr; // If no airport is found for the given city
}

Airline *Data::getAirline(string code) {
    for(auto airline : airlines) {
        if(airline->getCode() == code) {
            return airline;
        }
    }
    return nullptr;
}

unsigned long Data::numberAirports() {
    return airports.size();
}

unsigned long Data::numberAirlines() {
    return airlines.size();
}

unsigned long Data::numberFlights() {
    return flights.size();
}

set<Airport*> Data::getAirports() {
    return airports;
}

set<Airline*> Data::getAirlines() {
    return airlines;
}

set<Flight*> Data::getFlights() {
    return flights;
}