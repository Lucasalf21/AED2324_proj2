#include <iostream>
#include "Menu.h"
#include "Data.h"
#include "Filereader.h"
#include "GraphLoader.h"

void loadData(Data* data, Graph* g){
    auto* filereader = new Filereader(data);
    filereader->read();
    GraphLoader graphLoader;
    graphLoader.loadAirports(g, data);
    graphLoader.loadFlights(g, data);
}

int main() {
    cout << "Welcome to the Flight Management System!" << endl;
    Graph* g = new Graph();
    Data* data = new Data();
    loadData(data, g);
    Menu menu = Menu(data, g);
    return 0;
}

