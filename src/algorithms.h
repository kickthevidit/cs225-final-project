#pragma once

#include "airport.h"
#include <vector>
#include <iostream>

using namespace std;

/**
 * Conduct Breadth First Search on the graph adjacency matrix 
 * to find a path between start and end nodes.
*/
bool BFS(const int start, const int end, const vector<vector<double>>& matrix);

/**
 * Conduct Dijkstra's Algorithm to on a graph adjacency matrix
 * to find the shortest path wetween the source and destination nodes.
*/
vector<int> dijkstra(const vector<vector<double>>& matrix, const int source, const int dest);

/**
 * Helper Function for Dijkstra's Algorithm.
 * Given the destination node and a parents vector that defines
 * the parent in the shortest path, populate the path vector with
 *  the ordered path from source to destination
*/
void makePath(const vector<vector<double>>& matrix, const vector<int> parents, const int dest, vector<int>& path);