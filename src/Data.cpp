#include "Data.h"

void Data::newAirport(Airport* airport) {
    airports.insert(airport);
    graph.addVertex(airport);
}

void Data::newAirline(Airline* airline) {
    airlines.insert(airline);
}

Airport *Data::getAirport(string code) {
    return *airports.find(new Airport(code));
}

Airline *Data::getAirline(string code) {
    return *airlines.find(new Airline(code));
}

Data::Data() {
    graph = Graph<Airport*>();
    airlines = set<Airline*>();
    airports = set<Airport*>();
}

void Data::newFlight(Flight *flight) {
    graph.addEdge(flight->getSource(), flight->getDestination(), flight->getAirline());
}

