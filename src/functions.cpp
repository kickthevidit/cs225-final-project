#include "functions.h"

#include <cassert>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <list>
#include <fstream>

using std::isdigit;
using std::list;
using std::string;
using std::vector;

bool check_numeric(string num) {
	if (num.empty()) return false;

	unsigned start = (num[0] == '-') ? 0 : -1;

	return isdigit(num[start + 1]);
}

double process_numeric(string num) {
	return (check_numeric(num)) ? stod(num): -1 * std::numeric_limits<double>::max();
}


double calculateDist(double long1, double lat1, double long2, double lat2) {

	double lonDiff = long2 - long1;
    double latDiff = lat2 - lat1;
    
    //using Haversine Formula, R is radius of earth in KM
    long double ans = pow(sin(latDiff / 2), 2) +cos(lat1) * cos(lat2) * pow(sin(lonDiff / 2), 2);
    ans = 2 * asin(sqrt(ans));
    constexpr double EARTH_RADIUS = 6371;
    ans *= EARTH_RADIUS;
    return ans; 
}



void createDatasets(AirportMap &airport_map, AdjMatrix &adj, const V2D &airports, const V2D &routes) {
	assert(airport_map.empty() && adj.empty());

	int airport_count = 0;
	for (const auto &line : airports) {
		if (line.empty() || line.size() != 14) {
			// for (auto &a : line) std::cout << a << "|,|";
			// std::cout << '\n';
			continue;
		}

		int id = (int) process_numeric(line.at(0));

		Airport *temp = new Airport(airport_count++, id, line.at(1), line.at(4), process_numeric(line.at(6)), process_numeric(line.at(7)));

		// std::cout << "Id: " << id << '\n';

		airport_map[id] = temp;
	}

	// std::cout << "Number of Airports: " << airport_count << '\n';

	adj = AdjMatrix(airport_count, vector<double>(airport_count, -1.));

	for (const auto& line: routes) {
		if (line.size() != 9) continue;
		if (!check_numeric(line.at(3)) || !check_numeric(line.at(5)))
			continue;

		unsigned source_id = stoi(line.at(3));
		unsigned dest_id = stoi(line.at(5));

		// std::cout << "Source: " << source_id << '\n';
		// std::cout << "Destination: " << dest_id << '\n';

		try {

			auto *a1 = airport_map.at(source_id);
			auto *a2 = airport_map.at(dest_id);

			// std::cout << a1->longitude << ',' << a1->latitude << '\n';
			// std::cout << a2->longitude << ',' << a2->latitude << '\n';

			double dist = calculateDist(airport_map.at(source_id)->longitude, airport_map.at(source_id)->latitude, airport_map.at(dest_id)->longitude, airport_map.at(dest_id)->latitude);

			adj.at(airport_map.at(source_id)->adj_idx).at(airport_map.at(dest_id)->adj_idx) = dist;

		} catch (const std::out_of_range e) {
			// for (auto &a : line)
			// 	std::cout << a << "|,|";
			// std::cout << '\n';
			/*
				Ignore the airports causing an error. The issue is that some airports have commas in their names, to represent their cities which is being processed wrong by the csv parser.

				So for now we are ignoring these airports and once the csv parsing functions are rewritten we can remove this try catch block and include the ignored airports.

				TODO: rewrite csv parser to use content inside quotations and then remove try-catch
			*/
			continue;
		}
	}
}


void PrintAdjMatrix(const AdjMatrix& adj, unsigned range) {
	for (unsigned y = 0; y < adj.size() && y < range; ++y) {
		for (unsigned x = 0; x < adj.size() && x < range; ++x) {
			std::cout << adj.at(y).at(x) << '\t';
		}
		std::cout << '\n';
	}
}

void PrintAdjMatrix(const AdjMatrix &adj, std::string file_name, unsigned range) {
	std::ofstream ofs(file_name, std::ofstream::app);

	if (ofs.is_open()) {
		for (unsigned y = 0; y < adj.size() && y < range; ++y) {
			for (unsigned x = 0; x < adj.size() && x < range; ++x) {
				ofs << adj.at(y).at(x) << '\t';
			}
			ofs << '\n';
		}
	}
}