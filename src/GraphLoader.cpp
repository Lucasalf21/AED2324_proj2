//
// Created by lucasalf on 27-12-2023.
//

#include "GraphLoader.h"

void GraphLoader::loadAirports(Graph& g, Data* data) {
    for (auto a : data->getAirports()){
        g.addVertex(a);
    }
}

void GraphLoader::loadFlights(Graph &g, Data* data) {
    for (auto f : data->getFlights()){
        Vertex* source = g.findVertex(f->getSource());
        Vertex* dest = g.findVertex(f->getDestination());
        g.addEdge(source, dest, f->getAirline());
    }
}
