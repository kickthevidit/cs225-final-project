#pragma once

#include <string>
#include <iostream>
#include <map>

struct Airport {
    Airport(int adj_idx, int id, std::string name, std::string iata, double latitude, double longitude);

    friend std::ostream& operator<<(std::ostream& os, const Airport& ap);

    int adj_idx; // index in adjacency list
    int id;
    std::string name;
    std::string iata;
    double latitude;
    double longitude;
    std::map<int, int> dest; 
};


