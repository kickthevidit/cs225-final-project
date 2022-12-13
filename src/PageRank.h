#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include "airport.h"
#include <iostream>

class PageRank{
    public:
        //Constructs Markov Matrix from graph
        PageRank(const std::vector<std::vector<double>> &adjMatrix);

        //Prints vector of Airport ranks
        void print_rankVect(const std::map<int, Airport *>& AirportMap);

        //print rank matrix
        void print_rankMatrix();

        //Returns statinary vector of the rank of airports
        std::vector<double> genStationaryVect();

        std::vector<std::vector<double>> getMatrix();

    private:
        std::vector<std::vector<double>> rankMatrix;
        unsigned n;
};
