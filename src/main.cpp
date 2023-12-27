#include <iostream>
#include "Menu.h"
#include "Data.h"
#include "Filereader.h"
#include "GraphLoader.h"

int main() {
    cout << "Welcome to the Flight Management System!" << endl;
    Graph g;
    Data* data = new Data();
    auto* filereader = new Filereader(data);
    filereader->read();
    GraphLoader graphLoader;
    graphLoader.loadAirports(g, data);
    graphLoader.loadFlights(g, data);
    Menu menu = Menu(data, g);
    return 0;
}
