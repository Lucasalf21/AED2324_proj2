//
// Created by lucasalf on 26-12-2023.
//

#include "Menu.h"
#include <iostream>
#include <algorithm>

using namespace std;

Menu::Menu(Data* data, Graph* graph){
    this->data = data;
    g = graph;
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
                flightsFromAirport();
                break;
            case 5:
                flightsFromAirline();
                break;
            case 6:
                numberOfFlightsAirport();
                break;
            case 7:
                numberOfFlightsAirline();
                break;
            case 8:
                countriesFliesToAirport();
                break;
            case 9:
                countriesFliesToCity();
                break;
            case 10:
                destinationsAvailableAirport(); //Fiz mas nao consegui testar
                break;
            case 11:
                reachableDestinationsAirport(); //Fiz mas nao consegui testar
                break;
            case 12:
                maximumTrip(); //? TODO
                break;
            case 13:
                topAirports(); //TODO
                break;
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
    string source;
    string dest;
    cout << "Choose origin aiport: ";
    cin >> source;
    Airport* a1 = data->getAirport(source);
    if (a1 == nullptr){
        cout << "Airport not found!" << endl;
        return;
    }

    cout << "Choose destination airport: ";
    cin >> dest;
    Airport* a2 = data->getAirport(dest);
    if (a2 == nullptr){
        cout << "Airport not found!" << endl;
        return;
    }

    Vertex* s = g->findVertex(a1);
    Vertex* d = g->findVertex(a2);
    vector<pair<string, double>> bestRoute = g->dijkstra(s, d);

    cout << endl << "The best route from " << source << " to " << dest << " goes through:" << endl << endl;
    cout << bestRoute[0].first << "->";
    for (int i = 1;  i < bestRoute.size() - 2; i++){
        cout << bestRoute[i].first << "->";
    }
    cout << bestRoute[bestRoute.size() - 1].first << endl << endl;
    cout << "And travels a distance of " << bestRoute[bestRoute.size() - 1].second << " KM" << endl;
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
    cout << endl << "Enter the desired airport's code: " << endl;
    string sourceCode;
    cin >> sourceCode;
    for(auto flight : data->getFlights()) {
        if(flight->getSource()->getCode() == sourceCode) {
            flight->printFlight();
        }
    }
}

void Menu::flightsFromAirline() {
    cout << endl << "Enter the desired airline's code: " << endl;
    string airlineCode;
    cin >> airlineCode;
    for(auto flight : data->getFlights()) {
        if(flight->getAirline()->getCode() == airlineCode) {
            flight->printFlight();
        }
    }
    cout << endl;
}

void Menu::numberOfFlightsAirport() {
    cout << endl << "Enter the desired airport's code: " << endl;
    string sourceCode;
    cin >> sourceCode;
    int counter = 0;
    for(auto flight : data->getFlights()) {
        if(flight->getSource()->getCode() == sourceCode) {
            counter++;
        }
    }
    cout << endl << "Number of flights: " << counter << endl << endl;
}

void Menu::numberOfFlightsAirline() {
    cout << endl << "Enter the desired airline's code: " << endl;
    string airlineCode;
    cin >> airlineCode;
    int counter = 0;
    for(auto flight : data->getFlights()) {
        if(flight->getAirline()->getCode() == airlineCode) {
            counter++;
        }
    }
    cout << endl << "Number of flights: " << counter << endl << endl;
}

void Menu::countriesFliesToAirport() {
    cout << endl << "Enter the desired airport's code: " << endl;
    string sourceCode;
    vector<string> countries;
    for(auto flight : data->getFlights()) {
        if(flight->getSource()->getCode() == sourceCode && std::find(countries.begin(), countries.end(), flight->getDestination()->getCountry()) == countries.end()) {
            countries.push_back(flight->getDestination()->getCountry());
        }
    }

    sort(countries.begin(), countries.end());
    cout << endl << "Countries: " << endl;

    for(auto country : countries) {
        cout << country << endl;
    }

    cout << endl;
}

void Menu::countriesFliesToCity() {
    cout << endl << "Enter the desired city's name: " << endl;
    string cityName;
    cin.ignore();
    getline(cin, cityName);
    string cityCountry = checkCountry(cityName);
    vector<string> countries;
    for(auto flight : data->getFlights()) {
        if(flight->getSource()->getCountry() == cityCountry && flight->getSource()->getCity() == cityName
        && std::find(countries.begin(), countries.end(), flight->getDestination()->getCountry()) == countries.end()) {
            countries.push_back(flight->getDestination()->getCountry());
        }
    }

    std::sort(countries.begin(), countries.end());
    cout << endl << "Countries: " << endl;

    for(auto country : countries) {
        cout << country << endl;
    }

    cout << endl;
}

string Menu::checkCountry(string cityName) {
    string countryName;
    for(auto airport : data->getAirports()) {
        if(airport->getCity() == cityName) {
            if(countryName.empty()) countryName = airport->getCountry();
            if(countryName != airport->getCountry()){
                cout << "There are multiple countries with the same city name. Please enter the country name: " << endl;
                getline(cin, countryName);
                return countryName;
            }
        }
    }
    return countryName;
}

void Menu::destinationsAvailableAirport() {
    string airportCode;
    cout << endl << "Enter the desired airport's code: " << endl;
    cin >> airportCode;
    Airport* airport = data->getAirport(airportCode);
    if(airport == nullptr) {
        cout << "Airport not found!" << endl;
        return;
    }

    set<string> uniqueDestinations;  // Use a set to keep track of unique destinations

    cout << "Choose the type of destinations:" << endl;
    cout << "1. Airports" << endl;
    cout << "2. Cities" << endl;
    cout << "3. Countries" << endl;

    int choice;
    cout << "Enter your choice (1-3): ";
    cin >> choice;

    cout << endl << "Destinations available: " << endl;
    for(auto flight : data->getFlights()) {
        if(flight->getSource()->getCode() == airportCode) {
            string destination;
            switch (choice) {
                case 1:
                    destination = flight->getDestination()->getCode();  // Airports
                    break;
                case 2:
                    destination = flight->getDestination()->getCity();  // Cities
                    break;
                case 3:
                    destination = flight->getDestination()->getCountry();  // Countries
                    break;
                default:
                    cout << "Invalid choice. Exiting..." << endl;
                    return;
            }

            // Add the destination to the set
            uniqueDestinations.insert(destination);
        }
    }

    // Print the unique destinations
    for(const auto& destination : uniqueDestinations) {
        cout << destination << endl;
    }

    // Print the total number of unique destinations
    cout << "Total number of unique destinations: " << uniqueDestinations.size() << endl;
}

void Menu::reachableDestinationsAirport() {
    string airportCode;
    cout << endl << "Enter the desired airport's code: " << endl;
    cin >> airportCode;
    Airport* airport = data->getAirport(airportCode);
    if (airport == nullptr) {
        cout << "Airport not found!" << endl;
        return;
    }

    int maxStops;
    cout << "Enter the maximum number of stops: ";
    cin >> maxStops;

    int reachableCount = 0;

    // Choose the type of destinations
    cout << "Choose the type of destinations:" << endl;
    cout << "1. Airports" << endl;
    cout << "2. Cities" << endl;
    cout << "3. Countries" << endl;

    int choice;
    cout << "Enter your choice (1-3): ";
    cin >> choice;

    // Perform DFS to count reachable destinations within maxStops
    DFSCountReachableDestinations(airport, 0, maxStops, choice, reachableCount);

    cout << endl << "Number of reachable destinations within " << maxStops << " stops: " << reachableCount << endl;
}

// DFS helper function to count reachable destinations
void Menu::DFSCountReachableDestinations(Airport* currentAirport, int currentStops, int maxStops, int choice, int& reachableCount) {
    if (currentStops > maxStops) {
        return;  // Stop DFS if exceeding maximum stops
    }

    // Process the current airport as a reachable destination
    reachableCount++;

    // Output the type of destination based on user's choice
    switch (choice) {
        case 1:
            cout << currentAirport->getCode() << " ";  // Airports
            break;
        case 2:
            cout << currentAirport->getCity() << " ";  // Cities
            break;
        case 3:
            cout << currentAirport->getCountry() << " ";  // Countries
            break;
        default:
            cout << "Invalid choice. Exiting..." << endl;
            return;
    }

    // Get connected airports and continue DFS
    Vertex* currentVertex = g->findVertex(currentAirport);
    if (currentVertex != nullptr) {
        for (Edge& edge : currentVertex->adj) {
            Airport* nextAirport = edge.dest->info;
            DFSCountReachableDestinations(nextAirport, currentStops + 1, maxStops, choice, reachableCount);
        }
    }
}

void Menu::maximumTrip() {

}

void Menu::topAirports() {

}

