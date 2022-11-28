#include "utils.h"
#include <sstream>
#include <fenv.h>
#include <signal.h>
#include <vector>


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





