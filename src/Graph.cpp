#include "Graph.h"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>


bool Graph::addVertex(Airport *airport){
    Vertex* newAirport = new Vertex(airport);
    if (findVertex(newAirport->info) != nullptr){
        return false;
    }
    vertexSet.insert(newAirport);
    return true;
}

bool Graph::addEdge(Vertex *source, Vertex *dest, Airline *airline){
    if (findVertex(source->info) != nullptr && findVertex(dest->info) != nullptr){
        Airport* airport1 = source->info;
        Airport* airport2 = dest->info;
        double w = airport1->calculateDistance(airport2);
        Edge newConnection(dest, airline, w);
        source->adj.push_back(newConnection);
        dest->inVertices.push_back(source);
        return true;
    }
    return false;
}

set<Vertex *> Graph::getVertexSet() {
    return vertexSet;
}

vector<string> Graph::bfs(Vertex *source, Vertex *dest, set<Airline*> airlines){
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
            if (airlines.empty() || airlines.find(e.airline) != airlines.end()) {
                Vertex *w = e.dest;
                if (!w->visited) {
                    w->visited = true;
                    parentMap[w] = current;
                    q.push(w);
                }
            }
        }
    }
    return {};
}

set<vector<Vertex*>> Graph::findAllShortestPaths(Vertex* source, Vertex* dest, set<Airline*> airlines) {
    auto maxSize = bfs(source, dest, airlines).size();
    for (auto v : vertexSet) {
        v->visited = false;
    }

    set<vector<Vertex*>> result;
    queue<vector<Vertex *>> q;
    vector<Vertex*> currentPath;
    Vertex* current = findVertex(source->info);
    current->visited = true;
    currentPath.push_back(current);
    q.push(currentPath);

    while(!q.empty()){
        currentPath = q.front();
        q.pop();
        current = currentPath.back();

        if (current == dest){
            result.insert(currentPath);
            continue;
        }

        for (auto& e : current->adj){
            if (airlines.empty() || airlines.find(e.airline) != airlines.end()) {
                Vertex *w = e.dest;
                if (!w->visited) {
                    if (w != dest)
                        w->visited = true;
                    vector<Vertex *> newPath = currentPath;

                    if (newPath.size() < maxSize) {
                        newPath.push_back(w);
                        q.push(newPath);
                    }
                }
            }
        }
    }
    return result;
}

double Graph::findMaxDistance(Vertex *source) {
    double maxDistance = -1;
    for (auto vertex: vertexSet) {
        vertex->visited = false;
        vertex->distance = -1;
    }

    Vertex* v = source;
    queue<Vertex*> q;
    v->visited = true;
    v->distance = 0;
    q.push(source);

    while(!q.empty()){
        v = q.front();
        q.pop();
        for (auto& e : v->adj){
            auto w = e.dest;
            if (!w->visited){
                w->visited = true;
                w->distance = v->distance + 1;
                q.push(w);
            }
        }
    }

    for (auto vertex: vertexSet) {
        if (vertex->distance > maxDistance){
            maxDistance = vertex->distance;
        }
    }
    return maxDistance;
}

vector<pair<string, double>> Graph::dijkstra(Vertex *source, Vertex *dest){
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
        result.emplace_back(current->info->getCode(), current->distance);
        current = parentMap[current];
    }

    reverse(result.begin(), result.end());
    return result;
}

Vertex* Graph::findVertex(Airport* a){
    if(this->vertexSet.empty()){
        return nullptr;
    }
    for (auto vertex : vertexSet){
        if (vertex->info == a){
            return vertex;
        }
    }
    return nullptr;
}

void Graph::dfsArticulationPoints(Vertex* v, Vertex* parent, set<Vertex*>& articulationPoints, unordered_map<Vertex*, int>& disc, unordered_map<Vertex*, int>& low, int& time) {
    int children = 0;
    disc[v] = low[v] = ++time;

    for (auto& edge : v->adj) {
        Vertex* v1 = edge.dest;

        if (!v1->visited) {
            children++;
            v1->visited = true;

            dfsArticulationPoints(v1, v, articulationPoints, disc, low, time);

            low[v] = min(low[v], low[v1]);

            if ((parent == nullptr && children > 1) || (parent != nullptr && low[v1] >= disc[v])) {
                articulationPoints.insert(v);
            }
        } else if (v != parent) {
            low[v] = min(low[v], disc[v1]);
        }
    }
}

set<Vertex*> Graph::findArticulationPoints() {
    set<Vertex*> articulationPoints;
    unordered_map<Vertex*, int> disc;
    unordered_map<Vertex*, int> low;
    int time = 0;

    for (auto& v : vertexSet) {
        v->visited = false;
    }

    for (auto& v : vertexSet) {
        if (!v->visited) {
            v->visited = true;
            dfsArticulationPoints(v, nullptr, articulationPoints, disc, low, time);
        }
    }

    return articulationPoints;
}

set<Airport*> Graph::getAirportsByCity(const string& city, const string& country) {
    set<Airport*> airports;
    if (country.empty()) {
        for (auto &v: vertexSet) {
            if (v->info->getCity() == city) {
                airports.insert(v->info);
            }
        }
        return airports;
    }

    for (auto& v : vertexSet) {
        if (v->info->getCity() == city && v->info->getCountry() == country) {
            airports.insert(v->info);
        }
    }
    return airports;
}

Airport* Graph::getNearestAirportByCoordinates(double latitude, double longitude) {
    Airport* nearestAirport = nullptr;
    double minDistance = DBL_MAX;

    for (auto& v : vertexSet) {
        double distance = v->info->calculateDistance(latitude, longitude);
        if (distance < minDistance) {
            minDistance = distance;
            nearestAirport = v->info;
        }
    }

    return nearestAirport;
}

void Graph::makeUndirected() {
    for (auto& v : vertexSet) {
        for (auto& e : v->adj) {
            Vertex* dest = e.dest;
            double weight = e.weight;
            Airline* airline = e.airline;

            bool reverseEdgeExists = false;
            for (const auto& reverseEdge : dest->adj) {
                if (reverseEdge.dest == v) {
                    reverseEdgeExists = true;
                    break;
                }
            }

            if (!reverseEdgeExists) {
                Edge reverseEdge(v, airline, weight);
                dest->adj.push_back(reverseEdge);
            }
        }
    }
}
