#include "airport.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using namespace std;
int main() {
    vector<vector<string>> airports = fileToV2D("../data/airports.txt");
    vector<vector<string>> routes = fileToV2D("../data/routes.txt");
}