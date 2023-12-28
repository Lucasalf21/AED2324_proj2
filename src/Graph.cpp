#include "Graph.h"
#include <unordered_map>
#include <algorithm>
#include <iostream>


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

vector<pair<string, double>> Graph::dijkstra(Vertex *source, Vertex *dest) {
    vector<pair<string, double>> result;

    for (auto v : vertexSet) {
        v->distance = DBL_MAX;
    }

    set<pair<double, Vertex*>> priorityQueue;
    source->distance = 0;
    priorityQueue.insert({source->distance, source});
    unordered_map<Vertex*, Vertex*> parentMap;

    while (!priorityQueue.empty()) {
        Vertex* current = priorityQueue.begin()->second;
        priorityQueue.erase(priorityQueue.begin());

        for (auto& e : current->adj) {
            Vertex* w = e.dest;
            double newDistance = current->distance + e.weight;

            if (newDistance < w->distance) {
                priorityQueue.erase({w->distance, w});
                w->distance = newDistance;
                priorityQueue.insert({w->distance, w});

                parentMap[w] = current;
            }
        }
    }

    Vertex* current = findVertex(dest->info);

    while (current != nullptr) {
        result.push_back({current->info->getCode(), current->distance});
        current = parentMap[current];
    }

    reverse(result.begin(), result.end());
    return result;
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
