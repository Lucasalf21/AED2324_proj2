//
// Created by lucasalf on 26-12-2023.
//

#ifndef AED2324_PROJ2_MENU_H
#define AED2324_PROJ2_MENU_H

#include "Data.h"

class Menu {
public:
    Data* data;
    Graph* g;

    Menu(Data* data, Graph* graph);
    void statistics() const;
    void bestFlightOption(const set<Airline*>& airlines = {}) const;
    /**
     * @brief Prints the best flight option from a given airport to another. Complexity: O(n^2)
     * @param airlines Set of airlines to consider. If empty, all airlines are considered.
     */
    void bestFlightOptionByAirport(const set<Airline*>& airlines = {}) const;
    /**
     * @brief Prints the best flight option from a given city to another. Complexity: O(n^2)
     * @param airlines Set of airlines to consider. If empty, all airlines are considered.
     */
    void bestFlightOptionByCity(const set<Airline*>& airlines = {}) const;
    /**
     * @brief Prints the best flight option from a pair of coordinates to another. Complexity: O(n^2)
     * @param airlines Set of airlines to consider. If empty, all airlines are considered.
     */
    void bestFlightOptionByCoordinates(const set<Airline*>& airlines = {}) const;
    /**
     * @brief Prints the best flight option from a given source to a destination (any type). Complexity: O(n^2)
     * @param airlines Set of airlines to consider. If empty, all airlines are considered.
     */
    void bestFlightOptionMixed(const set<Airline*>& airlines = {}) const;
    void searchWithFilters() const;

    void choice1() const;
    void choice2() const;
    void choice3() const;
    void choice4() const;
    void choice5() const;
    void choice6() const;
    void choice7() const;
    void choice8() const;
    void choice9() const;


    void globalNumAirports() const;
    void globalNumFlights() const;
    void flightsFromAirport() const;
    void flightsFromCity() const;
    void flightsFromAirline() const;
    /**
     * @brief Prints the countries that are reachable from a certain airport. Complexity: O(n)
     */
    void countriesAnAirportFliesTo() const;
    /**
     * @brief Prints the countries that are reachable from a certain city. Complexity: O(n^2)
     */
    void countriesACityFliesTo() const;
    string checkCountry(const string& cityName) const; // auxiliary function
    /**
     * @brief Prints the number of airports, cities and countries reachable from an airport. Complexity: O(n^2)
     */
    void destinationsAvailableForAnAirport() const;
    /**
     * @brief Prints the number of airports, cities and countries reachable from an airport in a
     * specific number of lay-overs. Complexity: O(n^2)
     */
    void reachableDestinationsAirport() const;
    /**
     * @brief Prints the trip with the most lay-overs possible. Complexity: O(n^2)
     */
    void maximumTrip() const;
    /**
     * @brief Prints the top (x) airports by air traffic. Complexity: O(n log(n))
     */
    void topAirports() const;
    /**
     * @brief Prints the essential airports (if removed, some areas become unreachable). Complexity: O(n^3)
     */
    void essentialAirports() const;
};


#endif //AED2324_PROJ2_MENU_H
