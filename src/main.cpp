#include <iostream>
#include "Menu.h"
#include "Data.h"
#include "Filereader.h"
#include "GraphLoader.h"

int main() {
    Graph g;
    Data* data = new Data();
    auto* filereader = new Filereader(data);
    filereader->read();
    GraphLoader graphLoader;
    graphLoader.loadAirports(g, data);
    graphLoader.loadFlights(g, data);
    Menu menu = Menu(data);
    return 0;
}
