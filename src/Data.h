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

    /**
     * @brief Adds a new airport to the data structure. Complexity: O(1)
     * @param airport The airport to be added
     */
    void newAirport(Airport* airport);
    /**
     * @brief Adds a new airline to the data structure. Complexity: O(1)
     * @param airline The airline to be added
     */
    void newAirline(Airline* airline);
    /**
     * @brief Adds a new flight to the data structure. Complexity: O(1)
     * @param flight The flight to be added
     */
    void newFlight(Flight* flight);
    /**
     * @brief Returns a pointer to the airport with the given code. Complexity: O(n)
     * @param code The airport's code
     * @return A pointer to the airport
     */
    Airport* getAirport(const string& code);
    /**
     * @brief Returns a pointer to the airline with the given code. Complexity: O(n)
     * @param code The airline's code
     * @return A pointer to the airline
     */
    Airline* getAirline(const string& code);
    Flight* getFlight(Airport* source, Airport* destination, Airline* airline);
    set<Airport*> getAirports();
    set<Airline*> getAirlines();
    set<Flight*> getFlights();
};


#endif //AED2324_PROJ2_DATA_H
