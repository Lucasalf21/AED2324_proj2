#include "Data.h"

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
    return *airports.find(new Airport(code));
}

Airline *Data::getAirline(string code) {
    return *airlines.find(new Airline(code));
}

Data::Data() {
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