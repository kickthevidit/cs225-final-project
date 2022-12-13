#pragma once

#include "airport.h"
#include <vector>
#include <iostream>

using namespace std;

bool BFS(const int start, const int end, const vector<vector<double>>& matrix);

void printSolution(vector<int> dist);

int minDistance(vector<int> dist, vector<bool> sptSet);

void makePath(const vector<vector<double>>& matrix, const vector<int> parents, const int dest, vector<int>& path);

vector<int> dijkstra(const vector<vector<double>>& matrix, const int source, const int dest);