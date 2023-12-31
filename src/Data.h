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
    set<Airline*> airlines;
    set<Airport*> airports;
    set<Flight*> flights;
public:
    Data();

    void newAirport(Airport* airport);
    void newAirline(Airline* airline);
    void newFlight(Flight* flight);
    Airport* getAirport(const string& code);
    Airline* getAirline(const string& code);
    Flight* getFlight(Airport* source, Airport* destination, Airline* airline);
    set<Airport*> getAirports();
    set<Airline*> getAirlines();
    set<Flight*> getFlights();
};


#endif //AED2324_PROJ2_DATA_H
