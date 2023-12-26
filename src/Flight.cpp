//
// Created by Gonçalo Carvalho on 26/12/2023.
//

#include "Flight.h"

#include <utility>

Flight::Flight(Airport source, Airport destination, Airline airline) {
    this->source = std::move(source);
    this->destination = std::move(destination);
    this->airline = std::move(airline);
}

Airport Flight::getSource() {
    return source;
}

Airport Flight::getDestination() {
    return destination;
}

Airline Flight::getAirline() {
    return airline;
}
