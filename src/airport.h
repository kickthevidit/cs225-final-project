#pragma once

#include <string>
#include <map>

struct Airport {
    int id;
    std::string name;
    std::string iata;
    double latitude;
    double longitude;
    std::map<int, int> dest; 
};