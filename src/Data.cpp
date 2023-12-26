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
    return *airports.find(new Airport(code));
}

Airline *Data::getAirline(string code) {
    return *airlines.find(new Airline(code));
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

// Airports Graph

void Data::addAirportConnection(Airport *source, Airport *destination) {
    airportsGraph.addVertex(source);
    airportsGraph.addVertex(destination);
    airportsGraph.addEdge(source, destination);
}

bool Data::removeAirportConnection(Airport *source, Airport *destination) {
    return airportsGraph.removeEdge(source, destination);
}

vector<Airport *> Data::getConnectedAirports(Airport *airport) {
    vector<Airport*> connectedAirports;
    auto adjEdges = airportsGraph.findVertex(airport)->getAdj();
    for (const auto& edge : adjEdges) {
        connectedAirports.push_back(edge.getDest()->getInfo());
    }

    return connectedAirports;
}

bool Data::hasAirportConnection(Airport *source, Airport *destination) {
    return airportsGraph.hasEdge(source, destination);
}

// Airlines Graph

void Data::addAirlineConnection(Airline* source, Airline* destination) {
    airlinesGraph.addVertex(source);
    airlinesGraph.addVertex(destination);
    airlinesGraph.addEdge(source, destination);
}

bool Data::removeAirlineConnection(Airline* source, Airline* destination) {
    return airlinesGraph.removeEdge(source, destination);
}

vector<Airline*> Data::getConnectedAirlines(Airline* airline) {
    vector<Airline*> connectedAirlines;
    auto adjAirlines = airlinesGraph.findVertex(airline)->getAdj();
    for (const auto& edge : adjAirlines) {
        connectedAirlines.push_back(edge.getDest()->getInfo());
    }

    return connectedAirlines;
}

bool Data::hasAirlineConnection(Airline* source, Airline* destination) {
    return airlinesGraph.hasEdge(source, destination);
}