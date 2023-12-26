//
// Created by lucasalf on 26-12-2023.
//

#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu(Data* data){
    this->data = data;
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
                bestFlightOption(); //TODO
                break;
            case 3:
                searchWithFilters(); //TODO
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
             << " 2 - Global number of airlines" << endl
             << " 3 - Global number of flights" << endl
             << " 4 - Flights out of an airport" << endl
             << " 5 - Flights from an airline" << endl
             << " 6 - Number of flights per city" << endl
             << " 7 - Number of flights per airline" << endl
             << " 8 - Countries an airport flies to" << endl
             << " 9 - Countries a city flies to" << endl
             << " 10 - Destinations available for an airport" << endl
             << " 11 - Reachable destinations from an airport in a number of stops" << endl
             << " 12 - Maximum trip (?)" << endl
             << " 13 - Top airports with greatest air traffic capacity" << endl
             << endl
             << " 69 - Go back" << endl
             << " 0 - Exit" << endl
             << " __________________________________________________ " << endl
             << endl
             << "Choose the desired option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                globalNumAirports();
                break;
            case 2:
                globalNumAirlines();
                break;
            case 3:
                globalNumFlights();
                break;
            case 4:
                flightsFromAirport(); //TODO
                break;
            case 5:
                flightsFromAirline(); //TODO
                break;
            case 6:
                numberOfFlightsAirport(); //TODO
                break;
            case 7:
                numberOfFlightsAirline(); //TODO
                break;
            case 8:
                countriesFliesToAirport(); //TODO
                break;
            case 9:
                countriesFliesToCity(); //TODO
                break;
            case 10:
                destinationsAvailableAirport(); //TODO
                break;
            case 11:
                reachableDestinationsAirport(); //TODO
                break;
            case 12:
                maximumTrip(); //? TODO
                break;
            case 13:
                topAirports(); //TODO

            case 69:
                return;
            case 0:
                exit(0);
            default:
                cout << "Invalid option!" << endl;
        }
    }
}

//Menu options
void Menu::bestFlightOption() {

}

void Menu::searchWithFilters() {

}


//Statistics
void Menu::globalNumAirports() {
    cout << endl << "Number of airports: " << data->numberAirports() << endl << endl;
}

void Menu::globalNumAirlines() {
    cout << endl << "Number of airlines: " << data->numberAirlines() << endl << endl;
}

void Menu::globalNumFlights() {
    cout << endl << "Number of flights: " << data->numberFlights() << endl << endl;
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

void Menu::topAirports() {

}