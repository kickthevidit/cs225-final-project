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
    REQUIRE(BFS(2,3,test) == true);
    REQUIRE(BFS(3,2,test) == true);
    REQUIRE(BFS(0,3,test) == true);
    REQUIRE(BFS(3,0,test) == true);
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

// TEST_CASE("Large Matrix") {
//     AdjMatrix test = {{0,0.6,0,0,2.4,0,0,0},
//                       {7.4,0,0.3,5.8,0,0,0,0},
//                       {0,0,0,0,8.7,0,0,0},
//                       {0,0,0,0,0,0,0,0},
//                       {6.4,0,10.2,0,0,0,0,0},
//                       {0,3.2,0.8,0,0,0,0,0},
//                       {0,1.7,0,0,11.9,15.6,0,0},
//                       {1,0,1.2,0,8.8,0,0,0}};

//     REQUIRE(BFS(6,0,test) == true);
//     REQUIRE(BFS(4,7,test) == false);
//     REQUIRE(BFS(7,4,test) == true);
//     REQUIRE(BFS(5,8,test) == false);
//     REQUIRE(BFS(8,5,test) == true);
//     REQUIRE(BFS(4,5,test) == true);
//     REQUIRE(BFS(5,4,test) == true);
// }