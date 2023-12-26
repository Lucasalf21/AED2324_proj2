//
// Created by lucasalf on 26-12-2023.
//

#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu(){
    int choice = 1;

    while (choice != 0){
        cout << endl << " __________________________________________________ " << endl
             << " 1 - Statistics" << endl
             << " 2 - Find the best flight option" << endl
             << " 3 - Search with filters" << endl
             << endl
             << " 0 - Exit " << endl
             << " __________________________________________________ " << endl
             << endl
             << "Choose the desired option: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                statistics();
                break;
            case 2:
                //bestFlightOption();
                break;
            case 3:
                //searchWithFilters();
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

void Menu::statistics() {
    int choice = 1;

    while (choice != 69){
        cout << " __________________________________________________ " << endl
             << " 1 - Global number of airports " << endl
             << " 2 - Global number of flights" << endl
             << " 3 - Flights out of an airport" << endl
             << " 4 - Flights from an airline" << endl
             << " 5 - Number of flights per city" << endl
             << " 6 - Number of flights per airline" << endl
             << " 7 - Countries an airport flies to" << endl
             << " 8 - Countries a city flies to" << endl
             << " 9 - Destinations available for an airport" << endl
             << " 10 - Reachable destinations from an airport in a number of stops" << endl
             << " 11 - Maximum trip (?)" << endl
             << " 12 - Top airports with greatest air traffic capacity" << endl
             << endl
             << " 69 - Go back" << endl
             << " 0 - Exit" << endl
             << " __________________________________________________ " << endl
             << endl
             << "Choose the desired option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                globalAirports();
                break;
            case 2:
                globalFlights();
                break;
            case 3:
                flightsFromAirport();
                break;
            case 4:
                flightsFromAirline();
                break;
            case 5:
                numberOfFlightsAirport();
                break;
            case 6:
                numberOfFlightsAirline();
                break;
            case 7:
                countriesFliesToAirport();
                break;
            case 8:
                countriesFliesToCity();
                break;
            case 9:
                destinationsAvailableAirport();
                break;
            case 10:
                reachableDestinationsAirport();
                break;
            case 11:
                maximumTrip(); //?
                break;
            case 12:
                topAirports();

            case 69:
                return;
            case 0:
                exit(0);
            default:
                cout << "Invalid option!" << endl;
        }
    }
}

void Menu::bestFlightOption() {

}

void Menu::searchWithFilters() {

}

void Menu::topAirports() {

}

void Menu::globalAirports() {

}

void Menu::globalFlights() {

}

void Menu::flightsFromAirport() {

}

void Menu::flightsFromAirline() {

}

void Menu::numberOfFlightsAirport() {

}

void Menu::numberOfFlightsAirline() {

}

void Menu::countriesFliesToAirport() {

}

void Menu::countriesFliesToCity() {

}

void Menu::destinationsAvailableAirport() {

}

void Menu::reachableDestinationsAirport() {

}

void Menu::maximumTrip() {

}
