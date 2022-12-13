#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <vector>
#include <cmath>

#include "utils.h"
#include "airport.h"
#include "algorithms.h"
#include "PageRank.h"

typedef std::vector<std::vector<double>> AdjMatrix;

/**
 * All Test Varified with page rank function from MATH 257 hw
 * Screenshot of code in Result.md file
*/

TEST_CASE("Page Rank Test Stationary Vector simple small"){
    AdjMatrix matrix =  {{0,1,0,1},
                        {1,0,1,1},
                        {0,0,0,1},
                        {1,1,0,0}};
    //Transpose as our Page rank uses rows as vects
    AdjMatrix matrixT = matrix;
    for(unsigned i = 0; i < 4; i++){
        for(unsigned j = 0; j < 4; j++){
            matrixT[j][i] = matrix[i][j];
        }
    }
    PageRank rank(matrixT);
    std::vector<double> act_stationaryVect = rank.genStationaryVect();
    std::vector<double> exp_stationaryVect = {0.26666667, 0.33333333, 0.10000000, 0.30000000};

    std::vector<double> difference = exp_stationaryVect;
    for(unsigned i = 0; i < 4; i++){
        difference[i] = std::abs(exp_stationaryVect[i] - act_stationaryVect[i]);
    }

    for(const double& val : difference){
        REQUIRE(val < 0.01);
    }
}


TEST_CASE("Page Rank Test Stationary Vector small 0 vector case"){
    AdjMatrix matrix =  {{0,0,0,0},
                        {1,0,1,1},
                        {0,0,0,1},
                        {1,1,0,0}};
    //Transpose as our Page rank uses rows as vects
    AdjMatrix matrixT = matrix;
    for(unsigned i = 0; i < 4; i++){
        for(unsigned j = 0; j < 4; j++){
            matrixT[j][i] = matrix[i][j];
        }
    }
    PageRank rank(matrixT);
    std::vector<double> act_stationaryVect = rank.genStationaryVect();
    std::vector<double> exp_stationaryVect = {0, 0.4, 0.2, 0.4};

    std::vector<double> difference = exp_stationaryVect;
    for(unsigned i = 0; i < 4; i++){
        difference[i] = std::abs(exp_stationaryVect[i] - act_stationaryVect[i]);
    }

    for(const double& val : difference){
        REQUIRE(val < 0.1);
    }
}


TEST_CASE("Markov Matrix simple small"){
    AdjMatrix matrix =  {{0,1,0,1},
                        {1,0, 1,1},
                        {0,0,0,1},
                        {1,1,0,0}};
    //Transpose as our Page rank uses rows as vects
    AdjMatrix matrixT = matrix;
    for(unsigned i = 0; i < 4; i++){
        for(unsigned j = 0; j < 4; j++){
            matrixT[j][i] = matrix[i][j];
        }
    }
    PageRank rank(matrixT);
    AdjMatrix act_matrix = rank.getMatrix();
    AdjMatrix exp_matrix = {{0, 0.5, 0, 0.5},
                            {0.5, 0, 0, 0.5},
                            {0, 1, 0, 0},
                            {0.3333333333, 0.3333333333, 0.3333333333, 0}};
    for(unsigned i = 0; i < 4; i++){
        double sumAct = 0;
        for(unsigned j = 0; j < 4; j++){
            sumAct += act_matrix[i][j];
        }
        REQUIRE(std::abs(1 - sumAct) < 0.01);
    }
}

TEST_CASE("Markov Matrix small 0 vector case"){
    AdjMatrix matrix =  {{0,0,0,0},
                        {1,0,1,1},
                        {0,0,0,1},
                        {1,1,0,0}};
    //Transpose as our Page rank uses rows as vects
    AdjMatrix matrixT = matrix;
    for(unsigned i = 0; i < 4; i++){
        for(unsigned j = 0; j < 4; j++){
            matrixT[j][i] = matrix[i][j];
        }
    }
    PageRank rank(matrixT);
    AdjMatrix act_matrix = rank.getMatrix();
    AdjMatrix exp_matrix = {{0, 0.5, 0, 0.5},
                            {0, 0, 0, 1},
                            {0, 1, 0, 0},
                            {0, 0.5, 0.5, 0}};
    for(unsigned i = 0; i < 4; i++){
        double sumAct = 0;
        for(unsigned j = 0; j < 4; j++){
            sumAct += act_matrix[i][j];
        }
        REQUIRE(std::abs(1 - sumAct) < 0.01);
    }
}