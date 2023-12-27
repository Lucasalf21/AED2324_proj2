#include "Flight.h"

#include <utility>
#include <iostream>

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

void Flight::printFlight() {
    cout << source->getCountry() << " - " << source->getCity() << " (" << source->getName() << " - " << source->getCode() << ")"
         << " --> "
         << destination->getCountry() << " - " << destination->getCity() << " (" << destination->getName() << " - " << destination->getCode() << ")"
         << " | " << airline->getName() << " (" << airline->getCode() << ")" << endl;
}
