//
// Created by Gonçalo Carvalho on 26/12/2023.
//

#include <fstream>
#include <utility>
#include <sstream>
#include <iostream>
#include "Filereader.h"

Filereader::Filereader(Data *data) {
    this->data = data;
}

void Filereader::readAirports() {
    string line;
    ifstream airports("../files/airports.csv");
    getline(airports, line); //Skip first line (header)

    while(getline(airports, line)) {
        line = removeComma(std::move(line));
        istringstream iss(line);
        string code, name, city, country, stringLatitude, stringLongitude;
        iss >> code >> name >> city >> country >> stringLatitude >> stringLongitude;

        float latitude = stof(stringLatitude);
        float longitude = stof(stringLongitude);

        name = underscoreToSpace(std::move(name));
        city = underscoreToSpace(std::move(city));
        country = underscoreToSpace(std::move(country));

        auto* airport = new Airport(code, name, city, country, latitude, longitude);
        data->newAirport(airport);

    }
}

void Filereader::readAirlines() {
    string line;
    ifstream airlines("../files/airlines.csv");
    getline(airlines, line); //Skip first line (header)

    while(getline(airlines, line)) {
        line = removeComma(std::move(line));
        istringstream iss(line);
        string code, name, callsign, country;
        iss >> code >> name >> callsign >> country;

        name = underscoreToSpace(std::move(name));
        callsign = underscoreToSpace(std::move(callsign));
        country = underscoreToSpace(std::move(country));

        auto* airline = new Airline(code, name, callsign, country);
        data->newAirline(airline);
    }
}

void Filereader::readFlights(){
    string line;
    ifstream flights("../files/flights.csv");
    getline(flights, line); //Skip first line (header)

    while(getline(flights, line)) {
        line = removeComma(std::move(line));
        istringstream iss(line);
        string sourceCode, targetCode, airlineCode;
        Airport *source, *target;
        Airline *airline;

        iss >> sourceCode >> targetCode >> airlineCode;

        source = data->getAirport(sourceCode);
        target = data->getAirport(targetCode);
        airline = data->getAirline(airlineCode);

        data->newFlight(new Flight(source, target, airline));
    }
}

string Filereader::removeComma(string line) {
    string result = std::move(line);
    while (result.find(' ') != string::npos)
        result[result.find(' ')] = '_';

    while (result.find(',') != string::npos)
        result[result.find(',')] = ' ';

    return result;
}

string Filereader::underscoreToSpace(string line) {
    string result = std::move(line);
    while (result.find('_') != string::npos)
        result[result.find('_')] = ' ';

    return result;
}

void Filereader::read() {
    readAirports();
    readAirlines();
    readFlights();
}

