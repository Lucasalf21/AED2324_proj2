//
// Created by lucasalf on 27-12-2023.
//

#ifndef AED2324_PROJ2_GRAPHLOADER_H
#define AED2324_PROJ2_GRAPHLOADER_H

#include "Data.h"
#include "Graph.h"


class GraphLoader {
public:
    void loadAirports(Graph& g, Data* data);
    void loadFlights(Graph& g, Data* data);
};


#endif //AED2324_PROJ2_GRAPHLOADER_H
