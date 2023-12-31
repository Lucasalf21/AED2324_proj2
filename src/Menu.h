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
    void bestFlightOption(set<Airline*> airlines = {});
    void bestFlightOptionByAirport(set<Airline*> airlines = {});
    void bestFlightOptionByCity(set<Airline*> airlines = {});
    void bestFlightOptionByCoordinates(set<Airline*> airlines = {});
    void searchWithFilters();

    void choice1();
    void choice2();
    void choice3();
    void choice4();
    void choice5();
    void choice6();
    void choice7();
    void choice8();
    void choice9();

    void globalNumAirports();
    void globalNumAirlines();
    void globalNumFlights();
    void flightsFromAirport();
    void flightsFromCity();
    void flightsFromAirline();
    void countriesAnAirportFliesTo();
    void countriesACityFliesTo();
    string checkCountry(string cityName); // auxiliary function
    void destinationsAvailableForAnAirport();
    void reachableDestinationsAirport();
    void maximumTrip();
    void topAirports();
    void essentialAirports();

    void DFSCountReachableDestinations(Airport *currentAirport, int currentStops, int maxStops, int choice, int &reachableCount, set<string>& res);
};


#endif //AED2324_PROJ2_MENU_H
