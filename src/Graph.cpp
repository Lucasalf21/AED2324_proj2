#include "Graph.h"
#include <unordered_map>
#include <algorithm>


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

vector<string> Graph::bfs(Vertex *source, Vertex *dest) {
    vector<string> res;

    for (auto v: vertexSet) {
        v->visited = false;
    }

    queue<Vertex *> q;
    Vertex* current = findVertex(source->info);
    current->visited = true;
    q.push(current);
    unordered_map<Vertex*, Vertex*> parentMap;

    while (!q.empty()){
        current = q.front();
        q.pop();

        if (current == dest){
            while (current != nullptr){
                res.push_back(current->info->getCode());
                current = parentMap[current];
            }
            reverse(res.begin(), res.end());
            return res;
        }

        for (auto& e : current->adj){
            Vertex* w = e.dest;
            if (!w->visited){
                w->visited = true;
                parentMap[w] = current;
                q.push(w);
            }
        }
    }

    return {};
}

Vertex* Graph::findVertex(Airport* a) {
    for (auto vertex : vertexSet){
        if (vertex->info == a){
            return vertex;
        }
    }
    return nullptr;
}
