#ifndef AED2324_PROJ2_GRAPH_H
#define AED2324_PROJ2_GRAPH_H


#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <cfloat>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include "Airport.h"
#include "Airline.h"

struct Vertex;

struct Edge{
    Vertex* dest;
    Airline* airline;
    double weight;

    Edge(Vertex* d, Airline* a, double w) : dest(d), airline(a), weight(w) {};
};

struct Vertex{
    Airport* info;
    std::vector<Edge> adj;
    bool visited;
    double distance;
    set<Vertex*> inVertices;

    Vertex(Airport* in) : info(in), adj({}), visited(false), distance(DBL_MAX) {};
};

class Graph{
    set<Vertex*> vertexSet;

public:
    bool addVertex(Airport* airport);
    bool addEdge(Vertex* source, Vertex* dest, Airline* airline);
    set<Vertex*> getVertexSet();
    vector<string> bfs(Vertex* source, Vertex* dest, set<Airline*> airlines = {});
    set<vector<Vertex*>> findAllShortestPaths(Vertex* start, Vertex* end, set<Airline*> airlines = {});
    double findMaxDistance(Vertex* source);
    vector<pair<string, double>> dijkstra(Vertex* source, Vertex* dest);
    Vertex* findVertex(Airport* v);
    set<Vertex*> findArticulationPoints();

    void dfsArticulationPoints(Vertex *u, Vertex *parent, set<Vertex *> &articulationPoints,
                               unordered_map<Vertex *, int> &disc, unordered_map<Vertex *, int> &low,
                               int &time);
};

#endif //AED2324_PROJ2_GRAPH_H
