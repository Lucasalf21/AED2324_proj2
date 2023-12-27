#include "Graph.h"
#include <unordered_map>
#include <algorithm>


bool Graph::addVertex(Airport *airport) {
    Vertex* newAirport = new Vertex(airport);
    if (findVertex(newAirport->info) != nullptr){
        return false;
    }
    vertexSet.insert(newAirport);
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

set<Vertex *> Graph::getVertexSet() {
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

vector<pair<string, double>> Graph::dijkstra(Vertex* source, Vertex* dest){
    vector<pair<string, double>> res;

    for (auto v : vertexSet){
        v->visited = false;
        v->distance = DBL_MAX;
    }

    priority_queue<Vertex*, vector<Vertex*>, greater<>> pq;
    Vertex* current = findVertex(source->info);
    current->distance = 0;
    pq.push(current);

    unordered_map<Vertex*, Vertex*> parentMap;

    while (!pq.empty()){
        current = pq.top();
        pq.pop();
        current->visited = true;

        if (current == dest){
            while(current != nullptr){
                res.push_back({current->info->getCode(), current->distance});
                current = parentMap[current];
            }
            reverse(res.begin(), res.end());
            return res;
        }

        for (auto& e : current->adj){
            Vertex* w = e.dest;
            if (!w->visited){
                double newDistance = current->distance + e.weight;
                if (newDistance < w->distance){
                    w->distance = newDistance;
                    parentMap[w] = current;
                    pq.push(w);
                }
            }
        }
    }


    return {};
}

Vertex* Graph::findVertex(Airport* a) {
    if(this->vertexSet.empty()){
        return nullptr;
    }
    for (auto vertex : vertexSet){
        if (vertex->info->getCode() == a->getCode()){
            return vertex;
        }
    }
    return nullptr;
}
