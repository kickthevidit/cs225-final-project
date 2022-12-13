#include "algorithms.h"
#include <vector>
#include <set>
#include <queue>
#include <limits>

using namespace std;

typedef std::pair<double, int> Pair;

bool BFS(const int start, const int end, const vector<vector<double>>& matrix) {
    // edge cases
    if (start == end) {
        return true;
    }
    set<int> travelled;
    queue<int> check;
    check.emplace(start);

    while (!check.empty()) { // until queue is full
        int front = check.front();
        check.pop(); // get next neighbor
        if (front == end) { // if destination is reached
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

void makePath(const vector<vector<double>>& matrix, const vector<int> parents, const int dest, vector<int>& path) {
    if (dest == -1) {
        return;
    }
    makePath(matrix, parents, parents.at(dest), path); // recursively add next parents from the path
    path.push_back(dest);
}

vector<int> dijkstra(const vector<vector<double>>& matrix, const int source, const int dest) {
    if (source == dest) { return {source}; }

    int size = matrix.at(0).size();
    vector<double> dist(size);
    vector<bool> sptSet(size);
    vector<int> parents(size);
    parents.at(source) = -1;
    parents.at(dest) = -1;

    for (int i = 0; i < size; i++) {
        dist.at(i) = numeric_limits<double>::infinity();
        sptSet.at(i) = false;
    }
    dist[source] = 0;

    priority_queue<Pair, vector<Pair>, greater<Pair>> queue;
    queue.push(std::make_pair(0, source));
    
    while (!queue.empty()) {
        Pair curr = queue.top();
        queue.pop();

        double d = curr.first;
        int ind = curr.second;
        for (int i = 0; i < size; i++) {

            if (i == ind || sptSet.at(i) || matrix.at(ind).at(i) <= 0) continue;

            if (dist.at(i) > d + matrix.at(ind).at(i)) {
                dist.at(i) = d + matrix.at(ind).at(i);
                parents.at(i) = ind;
                queue.push(std::make_pair(d + matrix.at(ind).at(i), i));
            }
        }
        sptSet.at(ind) = true;
    }

    if (parents.at(dest) == -1) return {};

    vector<int> path;
    makePath(matrix, parents, dest, path);
    return path;
}