#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <vector>

#include "utils.h"
#include "airport.h"
#include "algorithms.h"

typedef std::vector<std::vector<double>> AdjMatrix;

TEST_CASE("Small Matrix") {
    AdjMatrix test = {{0,1,1,0},
                      {0,0,1,0},
                      {0,0,0,0},
                      {0,1,0,0}};

    REQUIRE(BFS(1,3,test) == false);
    REQUIRE(BFS(3,1,test) == true);
    REQUIRE(BFS(0,2,test) == true);
    REQUIRE(BFS(2,0,test) == false);
    REQUIRE(BFS(1,3,test) == false);
    REQUIRE(BFS(3,1,test) == true);
    REQUIRE(BFS(2,3,test) == false);
    REQUIRE(BFS(3,2,test) == true);
    REQUIRE(BFS(0,3,test) == false);
    REQUIRE(BFS(3,0,test) == false);

}

TEST_CASE("Small Matrix Undirected") {
    AdjMatrix test = {{0,1,0,1},
                      {1,0,1,0},
                      {0,1,0,0},
                      {1,0,0,0}};

    REQUIRE(BFS(0,0,test) == true);
    REQUIRE(BFS(0,1,test) == true);
    REQUIRE(BFS(1,0,test) == true);
    REQUIRE(BFS(1,2,test) == true);
    REQUIRE(BFS(2,1,test) == true);
}

TEST_CASE("Small Matrix Loop") {
    AdjMatrix test = {{0,1,0,0},
                      {0,0,1,0},
                      {0,0,0,1},
                      {1,0,0,0}};
    
    REQUIRE(BFS(0,0,test) == true);
    REQUIRE(BFS(0,1,test) == true);
    REQUIRE(BFS(1,0,test) == true);
    REQUIRE(BFS(1,3,test) == true);
    REQUIRE(BFS(3,1,test) == true);
}

TEST_CASE("Large Matrix") {

}