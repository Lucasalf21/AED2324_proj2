//
// Created by lucasalf on 27-12-2023.
//

#ifndef AED2324_PROJ2_GRAPHLOADER_H
#define AED2324_PROJ2_GRAPHLOADER_H

#include "Data.h"
#include "Graph.h"


class GraphLoader {
public:
    /**
     * @brief Loads the airports (vertices) from the data into the graph. Complexity: O(n)
     * @param g The graph to load the airports into
     * @param data The data to load the airports from
     */
    void loadAirports(Graph* g, Data* data);
    /**
     * @brief Loads the flights (edges) from the data into the graph. Complexity: O(n)
     * @param g The graph to load the flights into
     * @param data The data to load the flights from
     */
    void loadFlights(Graph* g, Data* data);
};


#endif //AED2324_PROJ2_GRAPHLOADER_H
