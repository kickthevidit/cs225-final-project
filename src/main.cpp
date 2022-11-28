#include "airport.h"
#include "utils.h"
#include "functions.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
int main() {
    vector<vector<string>> airports = fileToV2D("../data/airports.txt");
    vector<vector<string>> routes = fileToV2D("../data/routes.txt");

    // for(unsigned i =0; i < airports.size(); i++){
    //     for(unsigned j = 0; j < airports[i].size(); j++){
    //         cout<<airports[i][j];
    //     }
    //     cout<<endl;
    // }

    AirportMap airport_map;
    AdjMatrix adj;

    createDatasets(airport_map, adj, airports, routes);



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