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

    vector<vector<string>> airports = fileToV2D("../data/airports.txt");
    vector<vector<string>> routes = fileToV2D("../data/routes.txt");

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

    //a = [[0,1,0.,1.],[1.,0, 1, 1],[0,0,0,1], [1,1,0,0,]]

    // std::cout << "\nTesting PageRank\n";

    // vector<vector<double>> eg1 = {{0., 1., 0., 1.}, {1., 0., 1., 1.}, {0., 0., 0., 1.}, {1., 1, 0., 0.}};
    // vector < vector < double >> eg2((int) eg1.size(), vector<double>(eg1[0].size(), 0.));
    
    // for (unsigned i = 0; i < eg1.size(); ++i) {
    //     for (unsigned j = 0; j < eg1[i].size(); ++j) {
    //         eg2[j][i] = eg1[i][j];
    //     }
    // }

    // PageRank rank1(eg1);
    // auto out = rank1._genStationaryVect();

    // for (const auto& a: out) std::cout << a << ',';
    // std::cout << '\n';
}