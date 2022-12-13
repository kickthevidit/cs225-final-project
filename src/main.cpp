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
    std::ofstream ofs("../output/results.txt", std::ofstream::app);
    string start = argv[1];
    string end = argv[2];

    vector<vector<string>> airports = fileToV2D("../data/airports.txt");
    vector<vector<string>> routes = fileToV2D("../data/routes.txt");

    AirportMap airport_map;
    AirportMap airport_mapIdx;
    AdjMatrix adj;
    CodeToNodeMap nodeMap;

    ofs << "Args: " << start << ',' << end << '\n' ;

    ofs << "Reading Datasets...\n";
    createDatasets(airport_map, airport_mapIdx, nodeMap, adj, airports, routes);

    ofs << "Getting node IDs...\n";
    int id1 = nodeMap.at(start), id2 = nodeMap.at(end);

    ofs << "Creating Adjacency Matrix...\n";
    ofs << "See Adjacency Matrix in adjacency-matrix-500.txt\n";
    PrintAdjMatrix(adj, "../output/adjacency-matrix-500.txt", 500);

    ofs << "Conducting BFS...\n";
    std::cout << '\n';
    bool out = BFS(id1, id2, adj);
    ofs << (out) ? "Possible path found\n" :  "Possible path not found\n";

    ofs << "Conducting Disjkstra's...\n";
    std::cout << '\n';
    std::vector<int> path = dijkstra(adj, id1, id2);
    ofs << "Result Path: ";
    for (auto &a : path) ofs << a << '\t';
    ofs << '\n';


}