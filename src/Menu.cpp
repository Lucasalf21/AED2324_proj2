//
// Created by lucasalf on 26-12-2023.
//

#include "Menu.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <climits>

using namespace std;

Menu::Menu(Data* data, Graph* graph){
    this->data = data;
    g = graph;
    char choice = '1';

    while (true){
        cout << endl << " __________________________________________________ " << endl
             << " 1 - Statistics" << endl
             << " 2 - Find the best flight option" << endl
             << " 3 - Search with filters" << endl << endl

             << " 0 - Exit " << endl
             << " __________________________________________________ " << endl << endl

             << "Choose the desired option: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case '1':
                statistics();
                break;
            case '2':
                bestFlightOption();
                break;
            case '3':
                searchWithFilters();
                break;
            case '0':
                exit(0);
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

//Menu options
void Menu::bestFlightOption(const set<Airline*>& airlines) const {
    cout << "___________________BEST FLIGHT OPTION____________________" << endl
         << "Choose the type of destination:" << endl << endl
         << "1 - Airport" << endl
         << "2 - City" << endl
         << "3 - Coordinates" << endl
         << "4 - Mixed" << endl << endl

         << "b - Go back" << endl
         << "0 - Exit" << endl
         << " ________________________________________________________ " << endl << endl

         << " Choose the desired option: ";
    char choice;
    cin >> choice;
    cout << endl;
    switch (choice) {
        case '1':
            bestFlightOptionByAirport(airlines);
            break;
        case '2':
            bestFlightOptionByCity(airlines);
            break;
        case '3':
            bestFlightOptionByCoordinates(airlines);
            break;
        case '4':
            bestFlightOptionMixed(airlines);
            break;
        case 'b':
            return;
        case '0':
            exit(0);
        default:
            cout << "Invalid choice!" << endl;
    }
    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();
}

void Menu::bestFlightOptionByAirport(const set<Airline *>& airlines) const {
    bool filtered = !airlines.empty();
    string source;
    string dest;
    cout << "Choose origin airport: ";
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
    set<vector<Vertex *>> bestRoutes = g->findAllShortestPaths(s, d, airlines);

    cout << "Selected Airlines: " << endl;
    for (auto airline : airlines) {
        cout << airline->getCode() << " " << airline->getName() << endl;
    }

    if (bestRoutes.empty()) {
        if (filtered)
            cout << endl << "There are no routes from " << a1->getName() << " to " << a2->getName()
                 << " with the selected airlines." << endl << endl;
        else
            cout << endl << "There are no routes from " << a1->getName() << " to " << a2->getName() << "." << endl
                 << endl;

        return;
    }

    if (bestRoutes.size() > 1) {
        cout << endl << "The best routes from " << a1->getName() << " to " << a2->getName();
        if(filtered)
            cout << " with the selected airlines";
        cout << " go through:" << endl << endl;
    }
    else {
        cout << endl << "The best route from " << a1->getName() << " to " << a2->getName();
        if(filtered)
            cout << " with the selected airlines";
        cout << " goes through:" << endl << endl;
    }

    for(auto& route : bestRoutes) {
        cout << route[0]->info->getCode() << "->";
        for (int i = 1; i < route.size() - 1; i++) {
            cout << route[i]->info->getCode() << "->";
        }
        cout << route[route.size() - 1]->info->getCode() << endl;
    }

    cout << endl;
}

void Menu::bestFlightOptionByCity(const set<Airline *>& airlines) const {
    bool filtered = !airlines.empty();
    string source;
    string dest;
    cout << "Choose origin city: ";
    cin.ignore();
    getline(cin, source);
    string country = checkCountry(source);
    set<Airport*> a1 = g->getAirportsByCity(source, country);
    if (a1.empty()){
        cout << "Airport not found!" << endl;
        return;
    }

    cout << "Choose destination city: ";
    getline(cin, dest);
    string country2 = checkCountry(dest);
    set<Airport*> a2 = g->getAirportsByCity(dest, country2);
    if (a2.empty()){
        cout << "Airport not found!" << endl;
        return;
    }

    set<vector<Vertex *>> bestRoutes;
    int minSize = INT_MAX;

    for (auto airport1 : a1){
        for (auto airport2 : a2){
            Vertex* s = g->findVertex(airport1);
            Vertex* d = g->findVertex(airport2);
            set<vector<Vertex *>> routes = g->findAllShortestPaths(s, d, airlines);
            bestRoutes.insert(routes.begin(), routes.end());
        }
    }

    for (const auto& route : bestRoutes){
        if (route.size() < minSize){
            minSize = route.size();
        }
    }

    for (auto it = bestRoutes.begin(); it != bestRoutes.end();){
        if ((*it).size() > minSize){
            it = bestRoutes.erase(it);
        }
        else{
            it++;
        }
    }

    cout << "Selected Airlines: " << endl;
    for (auto airline : airlines) {
        cout << airline->getCode() << " " << airline->getName() << endl;
    }

    if (bestRoutes.empty()) {
        if (filtered)
            cout << endl << "There are no routes from " << source << " to " << dest
                 << " with the selected airlines." << endl << endl;
        else
            cout << endl << "There are no routes from " << source << " to " << dest << "." << endl
                 << endl;

        return;
    }

    if (bestRoutes.size() > 1) {
        cout << endl << "The best routes from " << source << " to " << dest;
        if(filtered)
            cout << " with the selected airlines";
        cout << " go through:" << endl << endl;
    }
    else {
        cout << endl << "The best route from " << source << " to " << dest;
        if(filtered)
            cout << " with the selected airlines";
        cout << " goes through:" << endl << endl;
    }

    for(auto& route : bestRoutes) {
        cout << route[0]->info->getCode() << "->";
        for (int i = 1; i < route.size() - 1; i++) {
            cout << route[i]->info->getCode() << "->";
        }
        cout << route[route.size() - 1]->info->getCode() << endl;
    }

    cout << endl;
}

void Menu::bestFlightOptionByCoordinates(const set<Airline *>& airlines) const {
    bool filtered = !airlines.empty();
    double sourceLat;
    double sourceLong;
    double destLat;
    double destLong;
    cout << "Choose origin coordinates: ";
    cin >> sourceLat >> sourceLong;
    Airport* a1 = g->getNearestAirportByCoordinates(sourceLat, sourceLong);
    if (a1 == nullptr){
        cout << "Airport not found!" << endl;
        return;
    }

    cout << "Choose destination coordinates: ";
    cin >> destLat >> destLong;
    Airport* a2 = g->getNearestAirportByCoordinates(destLat, destLong);
    if (a2 == nullptr){
        cout << "Airport not found!" << endl;
        return;
    }

    Vertex* s = g->findVertex(a1);
    Vertex* d = g->findVertex(a2);
    set<vector<Vertex *>> bestRoutes = g->findAllShortestPaths(s, d, airlines);

    cout << "Selected Airlines: " << endl;
    for (auto airline : airlines) {
        cout << airline->getCode() << " " << airline->getName() << endl;
    }

    if (bestRoutes.empty()) {
        if (filtered)
            cout << endl << "There are no routes from " << a1->getName() << " to " << a2->getName()
                 << " with the selected airlines." << endl << endl;
        else
            cout << endl << "There are no routes from " << a1->getName() << " to " << a2->getName() << "." << endl
                 << endl;

        return;
    }

    if (bestRoutes.size() > 1) {
        cout << endl << "The best routes from " << a1->getName() << " to " << a2->getName();
        if(filtered)
            cout << " with the selected airlines";
        cout << " go through:" << endl << endl;
    }
    else {
        cout << endl << "The best route from " << a1->getName() << " to " << a2->getName();
        if(filtered)
            cout << " with the selected airlines";
        cout << " goes through:" << endl << endl;
    }

    for(auto& route : bestRoutes) {
        cout << route[0]->info->getCode() << "->";
        for (int i = 1; i < route.size() - 1; i++) {
            cout << route[i]->info->getCode() << "->";
        }
        cout << route[route.size() - 1]->info->getCode() << endl;
    }

    cout << endl;
}

void Menu::bestFlightOptionMixed(const set<Airline*>& airlines) const {
    bool filtered = !airlines.empty();
    char choice1;
    cout << "Choose the type of the source (airport(1), city(2), coordinates(3)): ";
    cin >> choice1;

    string source;
    Airport* a1Source;
    set<Airport*> a2Source;
    string countrySource;
    double sourceLat;
    double sourceLong;
    switch (choice1){
        case '1':
            cout << "Choose origin airport: ";
            cin >> source;
            a1Source = data->getAirport(source);
            if (a1Source == nullptr){
                cout << "Airport not found!" << endl;
                return;
            }
            source = a1Source->getName();
            break;
        case '2':
            cout << "Choose origin city: ";
            cin.ignore();
            getline(cin, source);
            countrySource = checkCountry(source);
            a2Source = g->getAirportsByCity(source, countrySource);
            if (a2Source.empty()){
                cout << "Airport not found!" << endl;
                return;
            }
            break;
        case '3':
            cout << "Choose origin coordinates: ";
            cin >> sourceLat >> sourceLong;
            a1Source = g->getNearestAirportByCoordinates(sourceLat, sourceLong);
            if (a1Source == nullptr){
                cout << "Airport not found!" << endl;
                return;
            }
            source = a1Source->getName();
            break;
        default:
            cout << "Invalid choice!" << endl;
            return;
    }

    char choice2;
    cout << "Choose the type of the destination (airport(1), city(2), coordinates(3)): ";
    cin >> choice2;

    string dest;
    Airport* a1Dest;
    set<Airport*> a2Dest;
    string countryDest;
    double destLat;
    double destLong;
    switch (choice2){
        case '1':
            cout << "Choose destination airport: ";
            cin >> dest;
            a1Dest = data->getAirport(dest);
            if (a1Dest == nullptr){
                cout << "Airport not found!" << endl;
                return;
            }
            dest = a1Dest->getName();
            break;
        case '2':
            cout << "Choose destination city: ";
            cin.ignore();
            getline(cin, dest);
            countryDest = checkCountry(dest);
            a2Dest = g->getAirportsByCity(dest, countryDest);
            if (a2Dest.empty()){
                cout << "Airport not found!" << endl;
                return;
            }
            break;
        case '3':
            cout << "Choose destination coordinates: ";
            cin >> destLat >> destLong;
            a1Dest = g->getNearestAirportByCoordinates(destLat, destLong);

            if (a1Dest == nullptr){
                cout << "Airport not found!" << endl;
                return;
            }
            dest = a1Dest->getName();
            break;
        default:
            cout << "Invalid choice!" << endl;
            return;
    }

    set<vector<Vertex *>> bestRoutes;

    if (choice1 == '2' && choice2 == '2'){
        int minSize = INT_MAX;
        for (auto a : a2Source){
            for (auto b : a2Dest){
                Vertex* s = g->findVertex(a);
                Vertex* d = g->findVertex(b);
                set<vector<Vertex *>> routes = g->findAllShortestPaths(s, d, airlines);
                bestRoutes.insert(routes.begin(), routes.end());
            }
        }

        for (const auto& route : bestRoutes){
            if (route.size() < minSize){
                minSize = route.size();
            }
        }

        for (auto it = bestRoutes.begin(); it != bestRoutes.end();){
            if ((*it).size() > minSize){
                it = bestRoutes.erase(it);
            }
            else{
                it++;
            }
        }
    }
    else if (choice1 == '2'){
        int minSize = INT_MAX;
        for (auto a : a2Source){
            Vertex* s = g->findVertex(a);
            Vertex* d = g->findVertex(a1Dest);
            set<vector<Vertex *>> routes = g->findAllShortestPaths(s, d, airlines);
            bestRoutes.insert(routes.begin(), routes.end());
        }

        for (const auto& route : bestRoutes){
            if (route.size() < minSize){
                minSize = route.size();
            }
        }

        for (auto it = bestRoutes.begin(); it != bestRoutes.end();){
            if ((*it).size() > minSize){
                it = bestRoutes.erase(it);
            }
            else{
                it++;
            }
        }
    }
    else if (choice2 == '2'){
        int minSize = INT_MAX;
        for (auto a : a2Dest){
            Vertex* s = g->findVertex(a1Source);
            Vertex* d = g->findVertex(a);
            set<vector<Vertex *>> routes = g->findAllShortestPaths(s, d, airlines);
            bestRoutes.insert(routes.begin(), routes.end());
        }

        for (const auto& route : bestRoutes){
            if (route.size() < minSize){
                minSize = route.size();
            }
        }

        for (auto it = bestRoutes.begin(); it != bestRoutes.end();){
            if ((*it).size() > minSize){
                it = bestRoutes.erase(it);
            }
            else{
                it++;
            }
        }
    }
    else{
        Vertex* s = g->findVertex(a1Source);
        Vertex* d = g->findVertex(a1Dest);
        set<vector<Vertex *>> routes = g->findAllShortestPaths(s, d, airlines);
        bestRoutes.insert(routes.begin(), routes.end());
    }

    cout << "Selected Airlines: " << endl;
    for (auto airline : airlines) {
        cout << airline->getCode() << " " << airline->getName() << endl;
    }

    if (bestRoutes.empty()) {
        if (filtered)
            cout << endl << "There are no routes from " << source << " to " << dest
                 << " with the selected airlines." << endl << endl;
        else
            cout << endl << "There are no routes from " << source << " to " << dest << "." << endl
                 << endl;

        return;
    }

    if (bestRoutes.size() > 1) {
        cout << endl << "The best routes from " << source << " to " << dest;
        if(filtered)
            cout << " with the selected airlines";
        cout << " go through:" << endl << endl;
    }
    else {
        cout << endl << "The best route from " << source << " to " << dest;
        if(filtered)
            cout << " with the selected airlines";
        cout << " goes through:" << endl << endl;
    }

    for(auto& route : bestRoutes) {
        cout << route[0]->info->getCode() << "->";
        for (int i = 1; i < route.size() - 1; i++) {
            cout << route[i]->info->getCode() << "->";
        }
        cout << route[route.size() - 1]->info->getCode() << endl;
    }

    cout << endl;

}

void Menu::searchWithFilters() const {
    cout << "Choose the airlines you want to fly with" << endl
        <<  "Enter the airline's code or 0 to stop: " << endl;

    set<Airline*> airlines;
    string airlineCode;

    while(cin >> airlineCode){
        if (airlineCode == "0") break;
        Airline* airline = data->getAirline(airlineCode);
        if (airline == nullptr){
            cout << "Airline not found!" << endl;
            continue;
        }
        airlines.insert(airline);
    }

    bestFlightOption(airlines);
}

//statistics menu
void Menu::statistics() const {
    char choice = '1';

    while (true){
        cout << " _______________________STATISTICS_______________________ " << endl
             << " 1 - Global number of airports/flights" << endl
             << " 2 - Number of flights out of an airport " << endl
             << " 3 - Number of flights per city/airline " << endl
             << " 4 - Number of countries a airport/city flies to " << endl
             << " 5 - Number of destinations available from an airport " << endl
             << " 6 - Number of reachable destinations from an airport in a maximum number of lay-overs " << endl
             << " 7 - Maximum trip " << endl
             << " 8 - Top airports with greatest air traffic capacity " << endl
             << " 9 - Number of essential airports " << endl << endl

             << " b - Go back" << endl
             << " 0 - Exit" << endl
             << " ________________________________________________________ " << endl << endl

             << "Choose the desired option: ";
        cin >> choice;

        switch (choice) {
            case '1':
                choice1();
                break;
            case '2':
                choice2();
                break;
            case '3':
                choice3();
                break;
            case '4':
                choice4();
                break;
            case '5':
                choice5();
                break;
            case '6':
                choice6();
                break;
            case '7':
                choice7();
                break;
            case '8':
                choice8();
                break;
            case '9':
                choice9();
                break;

            case 'b':
                return;
            case '0':
                exit(0);
            default:
                cout << "Invalid option!" << endl;
        }
    }
}

//Statistics options
void Menu::choice1() const {
    cout << "Would you like to see the global number of airports(1) or the number of available flights(2)?" << endl;
    char choice;
    cout << "Option: ";
    cin >> choice;
    switch (choice) {
        case '1':
            globalNumAirports();
            break;
        case '2':
            globalNumFlights();
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
    cout << "Press enter to continue..."
            << endl;
    cin.ignore();
    cin.get();
}

void Menu::choice2() const {
    flightsFromAirport();
    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();
}

void Menu::choice3() const {
    cout << "Would you like to see the number of flights per city(1) or per airline(2)?" << endl;
    char choice;
    cout << "Option: ";
    cin >> choice;
    switch (choice) {
        case '1':
            flightsFromCity();
            break;
        case '2':
            flightsFromAirline();
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();
}

void Menu::choice4() const {
    cout << "Would you like to see the number of countries an airport(1) or a city(2) flies to?" << endl;
    char choice;
    cout << "Option: ";
    cin >> choice;
    switch (choice) {
        case '1':
            countriesAnAirportFliesTo();
            break;
        case '2':
            countriesACityFliesTo();
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();
}

void Menu::choice5() const {
    destinationsAvailableForAnAirport();
    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();
}

void Menu::choice6() const {
    reachableDestinationsAirport();
    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();
}

void Menu::choice7() const {
    maximumTrip();
    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();
}

void Menu::choice8() const {
    topAirports();
    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();
}

void Menu::choice9() const {
    essentialAirports();
    cout << "Press enter to continue...";
    cin.ignore();
    cin.get();
}

//Statistics

//choice 1
void Menu::globalNumAirports() const {
    cout << endl << "Number of airports: " << g->getVertexSet().size() << endl << endl;
}

void Menu::globalNumFlights() const {
    cout << endl << "Number of flights: " << data->getFlights().size() << endl << endl;
}

//choice 2
void Menu::flightsFromAirport() const {
    cout << endl << "Enter the desired airport's code: " << endl;
    string sourceCode;
    cin >> sourceCode;

    Airport* source = data->getAirport(sourceCode);
    if (source == nullptr){
        cout << endl << "Airport not found!" << endl;
        return;
    }

    int count = 0;
    set<Airline*> airlines;
    Vertex* airport = g->findVertex(source);
    for (auto& e : airport->adj){
        Airport* destination = data->getAirport(e.dest->info->getCode());
        Airline* airline = data->getAirline(e.airline->getCode());
        Flight* flight = data->getFlight(source, destination, airline);
        flight->printFlight();
        count++;
        airlines.insert(airline);
    }

    cout << endl << "Number of flights: " << count << endl << "From " << airlines.size() << " airlines" << endl << endl;
}

//choice 3
void Menu::flightsFromCity() const {
    cout << endl << "Enter the desired city's name: " << endl;
    string cityName;
    cin.ignore();
    getline(cin, cityName);
    string cityCountry = checkCountry(cityName);
    int count = 0;
    set<Airport*> airports = g->getAirportsByCity(cityName, cityCountry);
    for (auto a : airports){
        Vertex* airport = g->findVertex(a);
        for (auto& e : airport->adj){
            Airport* destination = data->getAirport(e.dest->info->getCode());
            Airline* airline = data->getAirline(e.airline->getCode());
            Flight* flight = data->getFlight(a, destination, airline);
            flight->printFlight();
            count++;
        }
    }

    cout << endl << "Number of flights: " << count << endl << endl;
}

void Menu::flightsFromAirline() const {
    cout << endl << "Enter the desired airline's code: " << endl;
    string airlineCode;
    cin >> airlineCode;
    int count = 0;
    for (auto v : g->getVertexSet()){
        for (auto& e : v->adj){
            if (e.airline->getCode() == airlineCode){
                Airport* source = data->getAirport(v->info->getCode());
                Airport* destination = data->getAirport(e.dest->info->getCode());
                Airline* airline = data->getAirline(e.airline->getCode());
                Flight* flight = data->getFlight(source, destination, airline);
                flight->printFlight();
                count++;
            }
        }
    }
    cout << endl << "Number of flights: " << count << endl << endl;
}

//choice 4
void Menu::countriesAnAirportFliesTo() const {
    cout << endl << "Enter the desired airport's code: " << endl;
    string sourceCode;
    cin >> sourceCode;
    Airport* source = data->getAirport(sourceCode);
    if (source == nullptr){
        cout << endl << "Airport not found!" << endl;
        return;
    }

    Vertex* airport = g->findVertex(source);
    set<string> countries;
    for (auto& e : airport->adj){
        countries.insert(e.dest->info->getCountry());
    }
    cout << "Countries:" << endl;
    for (auto& c : countries){
        cout << c << endl;
    }
    cout << endl << "Number of countries: " << countries.size() << endl << endl;
}

void Menu::countriesACityFliesTo() const {
    cout << endl << "Enter the desired city's name: " << endl;
    string cityName;
    cin.ignore();
    getline(cin, cityName);
    string cityCountry = checkCountry(cityName);
    set<string> countries;
    for (auto v : g->getVertexSet()){
        if (v->info->getCity() == cityName && v->info->getCountry() == cityCountry){
            for (auto& e : v->adj){
                if (countries.find(e.dest->info->getCountry()) == countries.end()){
                    countries.insert(e.dest->info->getCountry());
                }
            }
        }
    }

    cout << endl << "Countries: " << endl;

    for(const auto& country : countries) {
        cout << country << endl;
    }

    cout << endl << "Number of countries: " << countries.size() << endl << endl;
}

string Menu::checkCountry(const string& cityName) const {
    string countryName;
    for (auto v : g->getVertexSet()){
        if (v->info->getCity() == cityName){
            if (countryName.empty()){
                countryName = v->info->getCountry();
            }
            else if (countryName != v->info->getCountry()){
                cout << "There are multiple countries with the same city name! Please enter the country name: ";
                getline(cin, countryName);
                return countryName;
            }
        }
    }
    return countryName;
}

//choice 5
void Menu::destinationsAvailableForAnAirport() const {
    string airportCode;
    cout << endl << "Enter the desired airport's code: " << endl;
    cin >> airportCode;
    Airport* airport = data->getAirport(airportCode);
    if(airport == nullptr) {
        cout << "Airport not found!" << endl;
        return;
    }

    set<string> uniqueDestinations;

    cout << "Choose the type of destinations:" << endl;
    cout << "1. Airports" << endl;
    cout << "2. Cities" << endl;
    cout << "3. Countries" << endl;

    char choice;
    cout << "Enter your choice (1-3): ";
    cin >> choice;

    cout << endl << "Destinations available: " << endl;

    for (auto v : g->getVertexSet()){
        if (v->info->getCode() == airportCode){
            for (auto& e : v->adj){
                string destination;
                switch (choice) {
                    case '1':
                        destination = e.dest->info->getCode();
                        break;
                    case '2':
                        destination = e.dest->info->getCity();
                        break;
                    case '3':
                        destination = e.dest->info->getCountry();
                        break;
                    default:
                        cout << "Invalid choice. Exiting..." << endl;
                        return;
                }

                // Add the destination to the set
                uniqueDestinations.insert(destination);
            }
        }
    }

    for(const auto& destination : uniqueDestinations) {
        cout << destination << endl;
    }

    cout << endl << "Number of destinations: " << uniqueDestinations.size() << endl << endl;
}

//choice 6
void Menu::reachableDestinationsAirport() const {
    string airportCode;
    cout << endl << "Enter the desired airport's code: " << endl;
    cin >> airportCode;
    Airport* airport = data->getAirport(airportCode);
    if (airport == nullptr) {
        cout << "Airport not found!" << endl;
        return;
    }

    int maxStops;
    cout << "Enter the maximum number of lay-overs: ";
    cin >> maxStops;

    cout << "Choose the type of destinations:" << endl;
    cout << "1. Airports" << endl;
    cout << "2. Cities" << endl;
    cout << "3. Countries" << endl;

    char choice;
    cout << "Enter your choice (1-3): ";
    cin >> choice;

    set<string> res = g->countReachableVertices(g->findVertex(airport), maxStops, choice);

    cout << endl << "Number of reachable destinations within " << maxStops << " stops: " << res.size() << endl;
}

//choice 7
void Menu::maximumTrip() const {
    cout << endl << "Do you want to see the maximum trip for a specific airport? (y/n)" << endl;
    char choice;
    cin >> choice;
    vector<Vertex*> sources;
    map<Vertex*, vector<Vertex*>> destinations;
    double maxDistance = -1.0;

    if(choice == 'n' || choice == 'N') {
        for(auto airport : g->getVertexSet()) {
            double distance = g->findMaxDistance(airport);
            if(distance == maxDistance) {
                sources.push_back(airport);
            }
            else if(distance > maxDistance) {
                maxDistance = distance;
                sources.clear();
                sources.push_back(airport);
            }
        }
    }

    else if(choice == 'y' || choice == 'Y') {
        cout << endl << "Enter the sources airport's code: " << endl;
        string sourceCode;
        cin >> sourceCode;

        auto airport = data->getAirport(sourceCode);

        if(airport == nullptr){
            cout << "Airport not found!" << endl;
            return;
        }

        sources.push_back(g->findVertex(airport));
    }
    else {
        cout << "Invalid choice!" << endl;
        return;
    }

    for(auto source : sources) {
        maxDistance = g->findMaxDistance(source);
        for (auto dest: g->getVertexSet()) {
            if (!dest->visited) continue;
            if (dest->distance == maxDistance) {
                destinations[source].push_back(dest);
            }
        }
    }

    if(destinations.size() == 1 && destinations.begin()->second.size() == 1)
        cout << endl << "The maximum trip is: " << endl;
    else
        cout << endl << "The maximum trips are: " << endl;

    for(const auto& pair : destinations) {
        auto source = pair.first;
        for(auto dest : pair.second) {
            auto route = g->bfs(source, dest);
            for (int i = 0; i < route.size() - 1; i++) {
                cout << route[i] << " -> ";
            }
            cout << route[route.size() - 1] << endl;
        }
    }
    cout << endl;
}

//choice 8
bool compare(const pair<int, Vertex*>& a, const pair<int, Vertex*>& b){
    return a.first > b.first;
}

void Menu::topAirports() const {
    vector<pair<int, Vertex*>> airports;
    for (auto v : g->getVertexSet()){
        airports.emplace_back(v->adj.size() + v->inVertices.size(), v);
    }
    sort(airports.begin(), airports.end(), compare);

    cout << endl << "How many airports do you want to see? " << endl;
    int numAirports;
    cin >> numAirports;
    cout << endl;
    cout << "Top " << numAirports << " airports with greatest air traffic capacity: " << endl << endl;
    int count = 1;
    for (auto a : airports){
        if (count > numAirports){
            break;
        }
        cout << count << ". " << a.second->info->getName() << " (" << a.second->info->getCode() << ") - " << a.first << " flights" << endl;
        count++;
    }
    cout << endl;
}

//choice 9
void Menu::essentialAirports() const {
    cout << endl << "Number of essential airports: " << g->findArticulationPoints().size() << endl << endl;
}