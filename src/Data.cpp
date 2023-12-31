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

Airport *Data::getAirport(const string& code) {
    for(auto airport : airports) {
        if(airport->getCode() == code) {
            return airport;
        }
    }
    return nullptr;
}

Airline *Data::getAirline(const string& code) {
    for(auto airline : airlines) {
        if(airline->getCode() == code) {
            return airline;
        }
    }
    return nullptr;
}

Flight *Data::getFlight(Airport *source, Airport *destination, Airline *airline) {
    for(auto flight : flights) {
        if(flight->getSource() == source && flight->getDestination() == destination && flight->getAirline() == airline) {
            return flight;
        }
    }
    return nullptr;
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