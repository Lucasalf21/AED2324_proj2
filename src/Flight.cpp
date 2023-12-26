#include "Flight.h"

#include <utility>

Flight::Flight(Airport* source, Airport* destination, Airline* airline) {
    this->source = source;
    this->destination = destination;
    this->airline = airline;
}

Airport* Flight::getSource() {
    return source;
}

Airport* Flight::getDestination() {
    return destination;
}

Airline* Flight::getAirline() {
    return airline;
}
