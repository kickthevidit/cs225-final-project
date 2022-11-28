#include "utils.h"
#include <sstream>
#include <fenv.h>
#include <signal.h>
#include <vector>

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


//Library from UIUC CS225 MP schedule 


std::string file_to_string(const std::string& filename){
  std::ifstream text(filename);

  std::stringstream strStream;
  if (text.is_open()) {
    strStream << text.rdbuf();
  }
  return strStream.str();
}

std::string TrimRight(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(tmp.find_last_not_of(" ") + 1);
}

std::string TrimLeft(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(0, tmp.find_first_not_of(" "));
}

std::string Trim(const std::string & str) {
    std::string tmp = str;
    return TrimLeft(TrimRight(str));
}

int SplitString(const std::string & str1, char sep, std::vector<std::string> &fields) {
    std::string str = str1;
    std::string::size_type pos;
    while((pos=str.find(sep)) != std::string::npos) {
        fields.push_back(str.substr(0,pos));
        str.erase(0,pos+1);  
    }
    fields.push_back(str);
    return fields.size();
}

//Group additions (Own work)
/**
 * Function that converts file to two dim string equivalent
*/
V2D fileToV2D(const std::string& filename){
    V2D content;
    std::string file = file_to_string(filename);
    std::vector<std::string> line;
    std::vector<std::string> word;
    //break file into vector of lines
    int rowCount = SplitString(file, '\n', line);
    for(int i = 0; i < rowCount; i++){
        //break line into vector of words
        int elementCount = SplitString(line[i], ',', word);
        for(unsigned j = 0; j < word.size(); j++){
            word[j] = TrimLeft(word[j]);
            word[j] = TrimRight(word[j]);
            // if (word[j].empty()) word.erase(word.begin() + j);
        }
        if (word.empty()) continue;
        content.push_back(word);
        word.clear();
    }
    return content;
}
/**
 * Function that creates hashmap that maps source airport ID's to destination airport ID's
 * 
 * Params: Two dim string vectors of airport data and route data
 * 
 * Returns: Hash map that will be used for Airport class and Graphs
*/

std::unordered_map<std::string, std::vector<std::string>> genMap(const V2D airports, const V2D routes){
    //source airport ID: idx 3, dest airport ID: idx 5
    std::unordered_map<std::string, std::vector<std::string>> map;
    std::string cur_sourceAirportID;
    std::string cur_destAirportID;

    //Loop through routes and make source -> dest mapping based on if they exist
    for(unsigned i = 0; i < routes.size(); i++){
        //load current ID's
        if(routes[i].size() < 5){ continue; }
        cur_sourceAirportID = routes[i][3];
        cur_destAirportID = routes[i][5];
        if(!std::isdigit(cur_sourceAirportID[0])){continue;} //check to make sure ID is valid
        //check if airport exist in airport data (note sorted based on Airport ID)
        if(std::stoul(cur_sourceAirportID) < airports.size() && airports[std::stoi(cur_sourceAirportID)][0] == cur_sourceAirportID){
            //check if cur route is already initialized in map
            if(map.find(cur_sourceAirportID) != map.end()){
                map[cur_sourceAirportID].push_back(cur_destAirportID); //if exists add another destination
            }
            else{   //if not make new mapping for new airport
                std::vector<std::string> vect;
                vect.push_back(cur_destAirportID);
                map.insert(std::make_pair(cur_sourceAirportID, vect));
            }
        }
    }
    return map;

}




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


