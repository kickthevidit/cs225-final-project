#include "airport.h"
#include "algorithms.h"
#include "utils.h"
#include "PageRank.h"
// #include "functions.h"

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    string start = argv[1];
    string end = argv[2];

    cout << "Always fear what you don't understand\n";

    vector<vector<string>> airports = fileToV2D("../data/airports.txt");
    vector<vector<string>> routes = fileToV2D("../data/routes.txt");

    // cout << "Printing Airports\n";
    // for (unsigned i = 0; i < airports.size(); i++) {
    //     for(unsigned j = 0; j < airports[i].size(); j++){
    //         cout<<airports[i][j] << ',';
    //     }
    //     cout<<endl;
    // }

    // cout << "Printing Routes\n";
    // for (unsigned i = 0; i < routes.size(); i++) {
    //     for(unsigned j = 0; j < routes[i].size(); j++){
    //         cout << routes[i][j] << ',';
    //     }
    //     cout << endl;
    // }

    AirportMap airport_map;
    AirportMap airport_mapIdx;
    AdjMatrix adj;
    
    createDatasets(airport_map, airport_mapIdx, adj, airports, routes);

    //PrintAdjMatrix(adj, "adjacency-matrix-100.txt" ,100);
    std::cout << airport_map.at(3682)->iata << "|" << airport_map.at(3830)->iata << std::endl;
    std::vector<int> path = dijkstra(adj, airport_map.at(3682)->adj_idx, airport_map.at(3830)->adj_idx);
    for (int i : path) std::cout << airport_mapIdx.at(i)->iata << "->";
    std::cout << std::endl;

    //PageRank rank(adj);
    
    //rank.print_rankVect(airport_mapIdx);

}