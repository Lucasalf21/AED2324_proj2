#ifndef AED2324_PROJ2_FILEREADER_H
#define AED2324_PROJ2_FILEREADER_H

#include "Data.h"

using namespace std;

class Filereader {
private:
    Data* data;
public:
    Filereader(Data* data);
    void read();
    void readAirports();
    void readAirlines();
    void readFlights();

    static string removeComma(string linha);

    static string underscoreToSpace(string line);

};


#endif //AED2324_PROJ2_FILEREADER_H
