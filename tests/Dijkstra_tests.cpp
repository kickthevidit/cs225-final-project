#include <catch2/catch_test_macros.hpp>

#include <iostream>

#include "utils.h"
#include "airport.h"
#include "algorithms.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::vector<double>> AdjMatrix;
typedef std::vector<int> Path;

TEST_CASE("Undirected unweighted small matrix", "[dijkstra]") {
    AdjMatrix test = {{0,0,1,1},
                      {0,0,1,1},
                      {1,1,0,0},
                      {1,1,0,0}};
    
    Path e00 = {0};
    Path e01 = {0, 2, 1};
    Path e01_2 = {0, 3, 1};
    Path e02 = {0, 2};
    Path e20 = {2, 0};
    Path e13 = {1, 3};
    Path e31 = {3, 1};

    bool expected01 = dijkstra(test, 0, 1) == e01 || dijkstra(test,0,1) == e01_2;

    REQUIRE(dijkstra(test, 0, 0) == e00);
    REQUIRE(expected01 == true);
    REQUIRE(dijkstra(test, 0, 2) == e02);
    REQUIRE(dijkstra(test, 2, 0) == e20);
    REQUIRE(dijkstra(test, 1, 3) == e13);
    REQUIRE(dijkstra(test, 3, 1) == e31);
}

TEST_CASE("Directed unweighted small matrix", "[dijkstra]") {
    AdjMatrix test = {{0,1,1,1},
                      {1,0,0,0},
                      {0,1,0,0},
                      {1,0,0,0}};
    
    Path e00 = {0};
    Path e02 = {0, 2};
    Path e20 = {2, 1, 0};
    Path e13 = {1, 0, 3};
    Path e31 = {3, 0, 1};

    REQUIRE(dijkstra(test, 0, 0) == e00);
    REQUIRE(dijkstra(test, 0, 2) == e02);
    REQUIRE(dijkstra(test, 2, 0) == e20);
    REQUIRE(dijkstra(test, 1, 3) == e13);
    REQUIRE(dijkstra(test, 3, 1) == e31);
}

TEST_CASE("Undirected weighted matrix", "[dijkstra]") {
    AdjMatrix test = {{0,3,1,0,0},
                      {3,0,7,5,1},
                      {1,7,0,2,0},
                      {0,5,2,0,7},
                      {0,1,0,7,0}};

    Path e20 = {2, 0};
    Path e21 = {2, 0, 1};
    Path e22 = {2};
    Path e23 = {2, 3};
    Path e24 = {2, 0, 1, 4};
    Path e42 = {4, 1, 0, 2};

    REQUIRE(dijkstra(test, 2, 0) == e20);
    REQUIRE(dijkstra(test, 2, 1) == e21);
    REQUIRE(dijkstra(test, 2, 2) == e22);
    REQUIRE(dijkstra(test, 2, 3) == e23);
    REQUIRE(dijkstra(test, 2, 4) == e24);
    REQUIRE(dijkstra(test, 4, 2) == e42);
}

TEST_CASE("Directed weighted matrix", "[dijkstra]") {
    AdjMatrix test = {{0,4,3,0,0,0},
                      {0,0,5,2,0,0},
                      {0,15,0,7,0,0},
                      {0,0,0,0,2,0},
                      {4,4,0,0,0,6},
                      {0,0,0,0,0,0}};
    
    Path e02 = {0, 2};
    Path e04 = {0, 1, 3, 4};
    Path e10 = {1, 3, 4, 0};
    Path e21 = {2, 3, 4, 1};
    Path e35 = {3, 4, 5};
    Path e42 = {4, 0, 2};
    Path e50 = {};
    Path e55 = {5};

    REQUIRE(dijkstra(test, 0, 2) == e02);
    REQUIRE(dijkstra(test, 0, 4) == e04);
    REQUIRE(dijkstra(test, 1, 0) == e10);
    REQUIRE(dijkstra(test, 2, 1) == e21);
    REQUIRE(dijkstra(test, 3, 5) == e35);
    REQUIRE(dijkstra(test, 4, 2) == e42);
    REQUIRE(dijkstra(test, 5, 0) == e50);
    REQUIRE(dijkstra(test, 5, 5) == e55);
}