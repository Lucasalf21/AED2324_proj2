#ifndef AED2324_PROJ2_DATA_H
#define AED2324_PROJ2_DATA_H

#include "Graph.h"
#include "Airline.h"
#include "Airport.h"
#include "Flight.h"
#include <set>

using namespace std;
class Data {
private:
    Graph<Airport*> graph;
    set<Airline*> airlines;
    set<Airport*> airports;
public:
    Data();
    void newAirport(Airport* airport);
    void newAirline(Airline* airline);
    void newFlight(Flight* flight);
    Airport* getAirport(string code);
    Airline* getAirline(string code);

};


#endif //AED2324_PROJ2_DATA_H
