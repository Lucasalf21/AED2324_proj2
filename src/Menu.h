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
    void bestFlightOption(const set<Airline*>& airlines = {}) const;
    void bestFlightOptionByAirport(const set<Airline*>& airlines = {}) const;
    void bestFlightOptionByCity(const set<Airline*>& airlines = {}) const;
    void bestFlightOptionByCoordinates(const set<Airline*>& airlines = {}) const;
    void searchWithFilters() const;

    void choice1() const;
    void choice2() const;
    void choice3() const;
    void choice4() const;
    void choice5() const;
    void choice6();
    void choice7() const;
    void choice8() const;
    void choice9() const;

    void globalNumAirports() const;
    void globalNumFlights() const;
    void flightsFromAirport() const;
    void flightsFromCity() const;
    void flightsFromAirline() const;
    void countriesAnAirportFliesTo() const;
    void countriesACityFliesTo() const;
    string checkCountry(const string& cityName) const; // auxiliary function
    void destinationsAvailableForAnAirport() const;
    void reachableDestinationsAirport();
    void maximumTrip() const;
    void topAirports() const;
    void essentialAirports() const;

    void DFSCountReachableDestinations(Airport *currentAirport, int currentStops, int maxStops, int choice, int &reachableCount, set<string>& res);
};


#endif //AED2324_PROJ2_MENU_H
