#include "airport.h"
#include "utils.h"

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main(int argc, char* argv[]) {
    string start = argv[1];
    string end = argv[2];

    vector<vector<string>> airports = fileToV2D("../data/airports.txt");
    vector<vector<string>> routes = fileToV2D("../data/routes.txt");
}