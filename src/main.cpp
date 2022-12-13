#include "airport.h"
#include "algorithms.h"
#include "utils.h"
#include "PageRank.h"

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    std::ofstream ofs("output/results.txt", std::ofstream::app);
    string start = argv[1];
    string end = argv[2];

    vector<vector<string>> airports = fileToV2D("../data/airports.txt");
    vector<vector<string>> routes = fileToV2D("../data/routes.txt");

    AirportMap airport_map;
    AirportMap airport_mapIdx;
    AdjMatrix adj;
    CodeToNodeMap nodeMap;

    ofs << "Args: " << start << ',' << end << '\n' ;
    std::cout << "Args: " << start << ',' << end << '\n' ;

    ofs << "Reading Datasets...\n";
    std::cout << "Reading Datasets...\n";
    createDatasets(airport_map, airport_mapIdx, nodeMap, adj, airports, routes);

    ofs << "Getting node IDs...\n";
    std::cout << "Getting node IDs...\n";
    int id1 = nodeMap.at(start), id2 = nodeMap.at(end);

    ofs << "Creating Adjacency Matrix...\n";
    ofs << "See Adjacency Matrix in adjacency-matrix-500.txt\n";
    std::cout << "Creating Adjacency Matrix...\n";
    std::cout << "See Adjacency Matrix in adjacency-matrix-500.txt\n";
    PrintAdjMatrix(adj, "../output/adjacency-matrix-500.txt", 500);

    ofs << "Conducting BFS...\n";
    ofs << '\n';
    std::cout << "Conducting BFS...\n";
    std::cout << '\n';
    bool out = BFS(airport_map.at(id1)->adj_idx, airport_map.at(id2)->adj_idx, adj);
    ofs << ((out) ? "Possible path found\n" :  "Possible path not found\n");
    std::cout << ((out) ? "Possible path found\n" :  "Possible path not found\n");

    ofs << "Conducting Dijkstra's...\n";
    ofs << '\n';
    std::cout << "Conducting Dijkstra's...\n";
    std::cout << '\n';
    std::vector<int> path = dijkstra(adj, airport_map.at(id1)->adj_idx, airport_map.at(id2)->adj_idx);
    ofs << "Result Path: ";
    std::cout << "Result Path: ";
    for (auto &a : path) ofs << a << '\t';
    for (auto &a : path) std::cout << airport_mapIdx.at(a)->iata << '\t';
    ofs << '\n';
    std::cout << '\n';

    ofs << "Conducting PageRank...\n";
    std::cout << "Conducting PageRank...\n";
    PageRank p(adj);
    p.print_rankVect(airport_mapIdx);
}