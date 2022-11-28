#include "functions.h"

#include <cassert>
#include <cmath>

using std::string;
using std::vector;

void ProcessDataset(AirportList &airports, const V2D &airports_dataset) {
	assert(airports.empty());
	for (const auto &line : airports_dataset) {
		airports.push_back(new Airport(stoi(line.at(0)), line.at(1),line.at(4),stod(line.at(6)),stod(line.at(7))));
	}
}

double CalculateDist(double long1, double lat1, double long2, double lat2) {

	double lonDiff = long2 - long1;
    double latDiff = lat2 - lat1;
    
    //using Haversine Formula, R is radious of earth in KM
    long double ans = pow(sin(latDiff / 2), 2) +cos(lat1) * cos(lat2) * pow(sin(lonDiff / 2), 2);
    ans = 2 * asin(sqrt(ans));
    double R = 6371;
    ans *= R;
    return ans; 
}

AdjMatrix ProcessAdjacencyMatrix(AirportList &airports, const V2D &routes_dataset) {
	AdjMatrix adj(airports.size(), vector<double>(airports.size(), -1));

	for (const auto& line: routes_dataset) {
		Airport *a1 = airports.at(line.at(3) - 1);
		Airport *a2 = airports.at(line.at(5) - 1);

		adj.at(line.at(3) - 1).at(line.at(5) - 1) = CalculateDist(a1->long(), a1->lat(), a2->long(), a2->lat());
	}
}
