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


void shortestPath() { // Dijkstra's
    
}