#include "algorithms.h"
#include <vector>
#include <set>
#include <queue>

using namespace std;

bool BFS(const int start, const int end, const vector<vector<double>>& matrix) {
    if (start == end) {
        return true;
    }
    set<int> travelled;
    queue<int> check;
    check.emplace(start);

    while (!check.empty()) {
        int front = check.front();
        check.pop();
        if (front == end) {
            return true;
        }
        for (unsigned int i = 0; i < matrix.size(); i++) {
            int dist = matrix.at(front).at(i);
            if (dist > 0 && travelled.count(i) == 0) {
                check.emplace(i);
            }
        }
    }
    return false;
}

void printSolution(vector<int> dist) {
    cout << "Vertex \t Distance from Source" << endl;
    for (unsigned int i = 0; i < sizeof(dist); i++) {
        cout << i << " \t\t\t\t" << dist[i] << endl;
    }
}

int minDistance(vector<int> dist, vector<bool> sptSet) {
    int min = INT8_MAX, min_index;
 
    for (unsigned int v = 0; v < sizeof(dist); v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

void makePath(const vector<vector<double>>& matrix, const vector<int> parents, const int dest, vector<int>& path) {
    if (dest == -1) {
        return;
    }
    makePath(matrix, parents, parents.at(dest), path);
    path.push_back(dest);
}

vector<int> dijkstra(const vector<vector<double>>& matrix, const int source, const int dest) {
    int s = matrix.at(0).size();
    vector<int> dist(s);
    vector<bool> sptSet(s);

    for (int i = 0; i < s; i++) {
        dist.at(i) = (INT8_MAX);
        sptSet.at(i) = (false);
    }
    dist[source] = 0;

    vector<int> parents(s);

    parents.at(source) = -1;

    for (int i = 1; i < s; i++) {

        int nearestVertex = -1;
        int shortestDistance = INT8_MAX;
        for (int vertexIndex = 0; vertexIndex < s; vertexIndex++) {
            if (!sptSet[vertexIndex] && dist[vertexIndex] < shortestDistance) {
                nearestVertex = vertexIndex;
                shortestDistance = sptSet[vertexIndex];
            }
        }
 
        sptSet[nearestVertex] = true;
 
        for (int vertexIndex = 0; vertexIndex < s; vertexIndex++) {
            int edgeDistance = matrix[nearestVertex][vertexIndex];
 
            if (edgeDistance > 0 && ((shortestDistance + edgeDistance) < dist[vertexIndex])) {
                parents[vertexIndex] = nearestVertex;
                dist[vertexIndex] = shortestDistance + edgeDistance;
            }
        }
    }

    vector<int> path;
    makePath(matrix, parents, dest, path);
    return path;
}
