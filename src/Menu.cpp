//
// Created by lucasalf on 26-12-2023.
//

#include "Menu.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <climits>
#include <unistd.h>

using namespace std;

Menu::Menu(Data* data, Graph* graph){
    this->data = data;
    g = graph;
    int choice = 1;

    while (choice != 0){
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

//Menu options
void Menu::bestFlightOption(set<Airline*> airlines) {
    cout << "___________________BEST FLIGHT OPTION____________________" << endl
         << "Choose the type of destination:" << endl << endl
         << "1 - Airport" << endl
         << "2 - City" << endl
         << "3 - Coordinates" << endl << endl

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
        case 'b':
            return;
        case '0':
            exit(0);
        default:
            cout << "Invalid choice!" << endl;
    }
    cout << "Press enter to continue..."
         << endl;
    cin.ignore();
    cin.get();
}

void Menu::bestFlightOptionByAirport(set<Airline *> airlines) {
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

void Menu::bestFlightOptionByCity(set<Airline *> airlines) {
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

    for (auto route : bestRoutes){
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

void Menu::bestFlightOptionByCoordinates(set<Airline *> airlines) {
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

void Menu::searchWithFilters() {
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
void Menu::statistics() {
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
void Menu::choice1() {
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

void Menu::choice2() {
    flightsFromAirport();
    cout << "Press enter to continue..."
         << endl;
    cin.ignore();
    cin.get();
}

void Menu::choice3() {
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
    cout << "Press enter to continue..."
         << endl;
    cin.ignore();
    cin.get();
}

void Menu::choice4() {
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
    cout << "Press enter to continue..."
         << endl;
    cin.ignore();
    cin.get();
}

void Menu::choice5() {
    destinationsAvailableForAnAirport();
    cout << "Press enter to continue..."
         << endl;
    cin.ignore();
    cin.get();
}

void Menu::choice6() {
    reachableDestinationsAirport();
    cout << "Press enter to continue..."
         << endl;
    cin.ignore();
    cin.get();
}

void Menu::choice7() {
    maximumTrip();
    cout << "Press enter to continue..."
         << endl;
    cin.ignore();
    cin.get();
}

void Menu::choice8() {
    topAirports();
    cout << "Press enter to continue..."
         << endl;
    cin.ignore();
    cin.get();
}

void Menu::choice9() {
    essentialAirports();
    cout << "Press enter to continue..."
         << endl;
    cin.ignore();
    cin.get();
}

//Statistics

//choice 1
void Menu::globalNumAirports() {
    cout << endl << "Number of airports: " << data->numberAirports() << endl << endl;
}

void Menu::globalNumFlights() {
    cout << endl << "Number of flights: " << data->numberFlights() << endl << endl;
}

//choice 2
void Menu::flightsFromAirport() {
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
        cout << source->getCountry() << " - " << source->getCity() << " (" << source->getName() << " - " << source->getCode() << ")"
             << " --> "
             << destination->getCountry() << " - " << destination->getCity() << " (" << destination->getName() << " - " << destination->getCode() << ")"
             << " | " << airline->getName() << " (" << airline->getCode() << ")" << endl;
        count++;
        airlines.insert(airline);
    }

    cout << endl << "Number of flights: " << count << endl << "From " << airlines.size() << " airlines" << endl << endl;
}

//choice 3
void Menu::flightsFromCity() {
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
            cout << a->getCountry() << " - " << a->getCity() << " (" << a->getName() << " - " << a->getCode() << ")"
                 << " --> "
                 << destination->getCountry() << " - " << destination->getCity() << " (" << destination->getName() << " - " << destination->getCode() << ")"
                 << " | " << airline->getName() << " (" << airline->getCode() << ")" << endl;
            count++;
        }
    }

    cout << endl << "Number of flights: " << count << endl << endl;
}

void Menu::flightsFromAirline() {
    cout << endl << "Enter the desired airline's code: " << endl;
    string airlineCode;
    cin >> airlineCode;
    int count = 0;
    for(auto flight : data->getFlights()) {
        if(flight->getAirline()->getCode() == airlineCode) {
            flight->printFlight();
            count++;
        }
    }
    cout << endl << "Number of flights: " << count << endl << endl;
}

//choice 4
void Menu::countriesAnAirportFliesTo() {
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

void Menu::countriesACityFliesTo() {
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

    cout << endl << "Number of countries: " << countries.size() << endl << endl;
}

string Menu::checkCountry(string cityName) {
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
void Menu::destinationsAvailableForAnAirport() {
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
    cout << endl << "Number of destinations: " << uniqueDestinations.size() << endl << endl;
}

//choice 6
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

    set<string> res;

    // Perform DFS to count reachable destinations within maxStops
    DFSCountReachableDestinations(airport, 0, maxStops, choice, reachableCount, res);

    cout << endl << "Number of reachable destinations within " << maxStops << " stops: " << res.size() << endl;
}

// DFS helper function to count reachable destinations
void Menu::DFSCountReachableDestinations(Airport* currentAirport, int currentStops, int maxStops, int choice, int& reachableCount, set<string>& res) {

    if (currentStops > maxStops) {
        return;  // Stop DFS if exceeding maximum stops
    }

    // Process the current airport as a reachable destination
    reachableCount++;

    // Output the type of destination based on user's choice
    switch (choice) {
        case 1:
            res.insert(currentAirport->getCode());  // Airports
            break;
        case 2:
            res.insert(currentAirport->getCity());  // Cities
            break;
        case 3:
            res.insert(currentAirport->getCountry());  // Countries
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
            DFSCountReachableDestinations(nextAirport, currentStops + 1, maxStops, choice, reachableCount, res);
        }
    }
}

//choice 7
void Menu::maximumTrip() {
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

        /*cout << "TESTES: " << endl << "SourceCode inserido: " << sourceCode << endl
                                    << "Airport: " << airport->getCode() << endl;*/

        sources.push_back(g->findVertex(airport));
        //cout << "Sources size: " << sources.size() << endl;
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
void Menu::topAirports() {
    vector<Airport*> airports;
    for(auto airport : data->getAirports()) {
        airports.push_back(airport);
    }
    std::sort(airports.begin(), airports.end(), [](Airport* a, Airport* b) {
        return a->getNumFlights() > b->getNumFlights();
    });

    cout << endl << "How many airports do you want to see? " << endl;
    int numAirports;
    cin >> numAirports;
    cout << endl;
    cout << "Top " << numAirports << " airports with greatest air traffic capacity: " << endl << endl;
    for(int i = 0; i < numAirports; i++) {
        cout << airports[i]->getName() << " (" << airports[i]->getCode() << ") - " << airports[i]->getNumFlights() << " flights" << endl;
    }
    cout << endl;
}

//choice 9
void Menu::essentialAirports() {
    cout << endl << "Number of essential airports: " << g->findArticulationPoints().size() << endl << endl;
}

