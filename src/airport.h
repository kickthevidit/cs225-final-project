#pragma once

#include <string>
#include <iostream>
#include <map>

class Airport {
public:
    Airport(int id, std::string name, std::string iata, double latitude, double longitude);

    double long() const { return longitude; }
    double lat() const { return latitude; }

    friend std::ostream& operator<<(std::ostream& os, const Airport& ap);
private:
    int id;
    std::string name;
    std::string iata;
    double latitude;
    double longitude;
    std::map<int, int> dest; 
};


