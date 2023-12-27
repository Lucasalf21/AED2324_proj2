#include "Graph.h"


bool Graph::addVertex(Airport *airport) {
    Vertex* newAirport = new Vertex(airport);
    if (findVertex(newAirport->info) != NULL){
        return false;
    }
    vertexSet.push_back(newAirport);
    return true;
}

bool Graph::addEdge(Vertex *source, Vertex *dest, Airline *airline) {
    if (findVertex(source->info) != nullptr && findVertex(dest->info) != nullptr){
        Airport* airport1 = source->info;
        Airport* airport2 = dest->info;
        double w = airport1->calculateDistance(airport2);
        Edge newConnection(dest, airline, w);
        source->adj.push_back(newConnection);
        return true;
    }
    return false;
}

vector<Vertex *> Graph::getVertexSet() {
    return vertexSet;
}

bool vertexInAdj(vector<Edge> adj, Vertex* target){
    for (auto& e : adj){
        auto d = e.dest;
        if (d == target){
            return true;
        }
    }
    return false;
}

vector<string> Graph::bfs(Vertex *source, Vertex *dest) {
    vector<string> res;

    for (auto v: vertexSet) {
        v->visited = false;
    }

    queue<Vertex *> q;
    Vertex *v = findVertex(source->info);
    v->visited = true;
    q.push(v);

    while (!q.empty()) {
        v = q.front();
        q.pop();
        res.push_back(v->info->getCode());

        if (vertexInAdj(v->adj, dest)){
            res.push_back(dest->info->getCode());
            return res;
        }

        for (auto& e : v->adj){
            auto w = e.dest;
            if (!w->visited){
                w->visited = true;
                q.push(w);
            }
        }
    }

    vector<string> notFound;
    return notFound;
}

Vertex* Graph::findVertex(Airport* a) {
    for (auto vertex : vertexSet){
        if (vertex->info == a){
            return vertex;
        }
    }
    return nullptr;
}
