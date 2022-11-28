#include "airport.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
int main() {
    vector<vector<string>> airports = fileToV2D("../data/airports.txt");
    vector<vector<string>> routes = fileToV2D("../data/routes.txt");

    for(unsigned i =0; i < airports.size(); i++){
        for(unsigned j = 0; j < airports[i].size(); j++){
            cout<<airports[i][j];
        }
        cout<<endl;
    }
}