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
    void statistics();
    void bestFlightOption();
    void searchWithFilters();

    void globalNumAirports();
    void globalNumAirlines();
    void globalNumFlights();
    void flightsFromAirport();
    void flightsFromAirline();
    void numberOfFlightsAirport();
    void numberOfFlightsAirline();
    void countriesFliesToAirport();
    void countriesFliesToCity();
    string checkCountry(string cityName); // auxiliary function
    void destinationsAvailableAirport();
    void reachableDestinationsAirport();
    void maximumTrip();
    void topAirports();

};


#endif //AED2324_PROJ2_MENU_H
