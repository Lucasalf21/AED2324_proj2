#ifndef AED2324_PROJ2_AIRLINE_H
#define AED2324_PROJ2_AIRLINE_H

#include <string>

using namespace std;

class Airline {
private:
    string code;
    string name;
    string callsign;
    string country;
public:
    Airline();
    explicit Airline(string code, string name = "", string callsign = "", string country = "");
    string getCode();
    string getName();
    string getCallsign();
    string getCountry();
    bool operator <(const Airline& airline) const;
};


#endif //AED2324_PROJ2_AIRLINE_H
