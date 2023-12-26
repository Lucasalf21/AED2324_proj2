#ifndef AED2324_PROJ2_DATA_H
#define AED2324_PROJ2_DATA_H

#include "Graph.h"
#include "Airline.h"
#include "Airport.h"
#include "Flight.h"
#include <set>
#include <unordered_set>

using namespace std;
class Data {
private:
    Graph<Airport*> airportsGraph;
    Graph<Airline*> airlinesGraph;
    set<Airline*> airlines;
    set<Airport*> airports;
    set<Flight*> flights;
public:
    Data();
    void addAirportConnection(Airport* source, Airport* destination);
    bool removeAirportConnection(Airport* source, Airport* destination);
    vector<Airport*> getConnectedAirports(Airport* airport);
    bool hasAirportConnection(Airport* source, Airport* destination);
    void addAirlineConnection(Airline* source, Airline* destination);
    bool removeAirlineConnection(Airline* source, Airline* destination);
    vector<Airline*> getConnectedAirlines(Airline* airline);
    bool hasAirlineConnection(Airline* source, Airline* destination);
    void newAirport(Airport* airport);
    void newAirline(Airline* airline);
    void newFlight(Flight* flight);
    Airport* getAirport(string code);
    Airline* getAirline(string code);
    unsigned long numberAirports();
    unsigned long numberAirlines();
    unsigned long numberFlights();
};


#endif //AED2324_PROJ2_DATA_H
