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


std::string file_to_string(const std::string& filename){
  /**
   * Function takes in a filename as string
   * returns the contents of the file as a string.
  */
  std::ifstream text(filename);

  std::stringstream strStream;
  if (text.is_open()) {
    strStream << text.rdbuf();
  }
  return strStream.str();
}

std::string TrimRight(const std::string & str) {
	/**
	 * Input: a string
	 * Processing: Removes all whitespaces at the end of the string
	 * Output: a string
	*/
    std::string tmp = str;
    return tmp.erase(tmp.find_last_not_of(" ") + 1);
}

std::string TrimLeft(const std::string & str) {
	/**
	 * Input: a string
	 * Processing: Removes all whitespaces at start of the string
	 * Output: a string
	*/
    std::string tmp = str;
    return tmp.erase(0, tmp.find_first_not_of(" "));
}

void removeQuotes(std::string& str) {
	/**
	 * Input: a string
	 * Processing: Removes all quote characters from the start and end of the string
	 * Output: the string with all quotes removed
	*/
	if (str.find('\"') != std::string::npos){
		str.pop_back();
		str[0] = ' ';
	}
}

std::string Trim(const std::string & str) {
	/**
	 * Input: a string
	 * Processing: Removes all whitespaces from the start and end of the string.
	 * Output: the string with all whitespaces removed
	*/
    std::string tmp = str;
    //Removes Double quotes
	removeQuotes(tmp);
	tmp = TrimLeft(TrimRight(tmp));
    return tmp;
}

int SplitString(const std::string & str1, char sep, std::vector<std::string> &fields) {
	/**
	 * Input: string str1, char sep, vector<string>& fields
	 * Processing: splits the string into different strings when encountering the char and places all split elements into the vector<string>
	 * Output: the length of fields i.e. the number split elements
	*/
    std::string str = str1;
    std::string::size_type pos;
    while((pos=str.find(sep)) != std::string::npos) {
        fields.push_back(str.substr(0,pos));
        str.erase(0,pos+1);  
    }
    fields.push_back(str);
    return fields.size();
}


V2D fileToV2D(const std::string& filename){
	/**
	* Input: file path as string
	* Processing: takes content of file and organises it into a 2 dim vector splitting using whitespaces and newline characters
	* Output: a 2d vector
	*/
    V2D content;
    std::string file = file_to_string(filename);
    std::vector<std::string> line;
    std::vector<std::string> word;
    //break file into vector of lines
    int rowCount = SplitString(file, '\n', line);
    for(int i = 0; i < rowCount-1; i++){
        //break line into vector of words
        int elementCount = SplitString(line[i], ',', word);
        for(unsigned j = 0; j < word.size(); j++){
            word[j] = Trim(word[j]);
        }
        if(word.empty()) continue;
		if (filename == "../data/airports.txt") {
			if (word[3] == "United States") 
				content.push_back(word);
		} else content.push_back(word);
		word.clear();
    }
    return content;
}

bool check_numeric(string num) {
	/**
	 * Input: Takes in a string
	 * Output: Returns if the string is a valid decimal number
	*/
	if (num.empty()) return false;

	unsigned start = (num[0] == '-') ? 0 : -1;

	return isdigit(num[start + 1]);
}

double stringToNegativeDouble(string num) {
	/**
	 * Input: A string
	 * Output: If the string is numeric, return the string as a double. Else, return ((double) -1 * INF)
	*/

	return (check_numeric(num)) ? stod(num): -1 * std::numeric_limits<double>::max();
}


double calculateDist(double long1, double lat1, double long2, double lat2) {
	/**
	 * Input: latitude-longitude of 2 locations
	 * Output: the distance between the two locations using Haversine Formula
	*/

	// calculate the distance between latitude and longitude
	double lonDiff = long2 - long1;
    double latDiff = lat2 - lat1;
    
    //using Haversine Formula, R is radius of earth in KM
    long double ans = pow(sin(latDiff / 2), 2) +cos(lat1) * cos(lat2) * pow(sin(lonDiff / 2), 2);
    ans = 2 * asin(sqrt(ans));
    constexpr double EARTH_RADIUS = 6371;
    ans *= EARTH_RADIUS;
    return ans; 
}

void createDatasets(AirportMap &airport_mapSource, AirportMap &airport_mapIdx, CodeToNodeMap& nodeMap ,AdjMatrix &adj, const V2D &airports, const V2D& routes) {
	/**
	 * Processing our datasets from 2d vector form to an adjacency matrix and a map with key-value pairs IATA number-Airport.
	*/

	assert(airport_mapSource.empty() && adj.empty());

	// Getting airport data from the airport dataset

	int airport_count = 0;
	for (const auto &line : airports) {
		if (line.empty() || line.size() != 14) continue;

		int id = (int) stringToNegativeDouble(line.at(0));
		string iata = line.at(4);

		Airport *temp = new Airport(airport_count, id, line.at(1), iata, stringToNegativeDouble(line.at(6)), stringToNegativeDouble(line.at(7)));

		nodeMap[iata] = id;
		airport_mapSource[id] = temp;
		airport_mapIdx[airport_count] = temp;
		airport_count++;
	}

	// initializing adjacency matrix
	adj = AdjMatrix(airport_count, vector<double>(airport_count, -1.));

	// processing routes
	V2D unused_airports;
	for (const auto& line: routes) {
		if (line.size() != 9) continue;
		if (!check_numeric(line.at(3)) || !check_numeric(line.at(5))) continue;

		unsigned source_id = stoi(line.at(3));
		unsigned dest_id = stoi(line.at(5));

		try {
			auto *a1 = airport_mapSource.at(source_id);
			auto *a2 = airport_mapSource.at(dest_id);

			if (!a1 || !a2) continue;

			double dist = calculateDist(airport_mapSource.at(source_id)->longitude, airport_mapSource.at(source_id)->latitude, airport_mapSource.at(dest_id)->longitude, airport_mapSource.at(dest_id)->latitude);

			adj.at(airport_mapSource.at(source_id)->adj_idx).at(airport_mapSource.at(dest_id)->adj_idx) = dist;
		} catch (const std::out_of_range e) {
			unused_airports.push_back(line);
			continue;
		}
	}

}

void PrintAdjMatrix(const AdjMatrix& adj, unsigned range) {
	/**
	*  Given a 2d vector of adjacency matrix print it out 
	*/
	for (unsigned y = 0; y < adj.size() && y < range; ++y) {
		for (unsigned x = 0; x < adj.size() && x < range; ++x) {
			std::cout << adj.at(y).at(x) << '\t';
		}
		std::cout << '\n';
	}
}

void PrintAdjMatrix(const AdjMatrix &adj, std::string file_name, unsigned range) {
	/**
	 *  Write part of an adjacency matrix of size n*n onto a file with specified file path. 
	 * */
	
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
