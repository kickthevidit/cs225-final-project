#include "airport.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <algorithm>

int main() {

    std::vector<Airport> airports = loadAirports("../data/airports.csv");

    std::cout << airports.at(230) << std::endl;
    // std::ifstream file("../data/airport.csv");

    // std::string line;
    // while (std::getline(file, line)) {
    //     std::cout << line << std::endl;
    // }

    // auto vec = parse(line, '\n');

    // //std::cout << line.find(, ',') << std::endl;

    // std::cout << vec.size() << std::endl;
    // for (auto s : vec) {
    //     std::cout << s << std::endl;
    // }
}