#include "PageRank.h"

/**
 * Constructs Markov Matrix from graph
*/
PageRank::PageRank(const std::vector<std::vector<double>> &adjMatrix){
    //copy adj matrix, we can uses weights to determine if route exist
    rankMatrix = adjMatrix;
    n = rankMatrix.size();
    for(unsigned i = 0; i < n; i++){
        double colCount = 0; //count the degree of node. Used for normalizing vector
        for(unsigned j = 0; j < n; j++){
            if(rankMatrix[i][j] <= 0) { 
                rankMatrix[i][j] = 0; 
            } else {
                rankMatrix[i][j] = 1; //replace weight with 1
                colCount++;
            }
        }
        //Divide by zero case, gets filled with 1/n
        if(colCount == 0){
            for(unsigned j = 0; j < n; j++){
                rankMatrix[i][j] = 1 / double(n);
            }
        } else {
            for(unsigned j = 0; j < n; j++){
                if (rankMatrix[i][j] != 0)
                    rankMatrix[i][j] = rankMatrix[i][j] / colCount;
            }
        }
    }
}

/**
 * Returns stationary vector of airport ranks via power iteration
*/
std::vector<double> PageRank::_genStationaryVect(){
    std::vector<double> vect(n);

    //intialize arbitratry vect
    for(unsigned int i = 0; i < n; i++){
        vect[i] = 1.0/n;
    }
    double prevVal = 0;
    do{
        prevVal = vect[0]; //update prev val
        std::vector<double> copyVect = vect;
        for (unsigned i = 0; i < n; i++) {
            double sum = 0;
            for(unsigned j = 0; j < n; j++){
                sum += rankMatrix[j][i] * double(copyVect[j]);
            }
            vect[i] = sum;
        }
    }   while(!(std::abs(vect[0] - prevVal) < 0.000001));
    return vect;
}



/**
 * Prints sorted vector of Airport ranks
*/
void PageRank::print_rankVect(const std::map<int, Airport *>& AirportMap){
    std::vector<double> stationaryVect = _genStationaryVect();
    std::vector<Airport> rankList;

    for(unsigned i = 0; i < 25; i++){
        int max_index = std::distance(stationaryVect.begin(), std::max_element(stationaryVect.begin(), stationaryVect.end()));
        rankList.push_back(*(AirportMap.at(max_index)));
        std::cout << i+1 << ":" << rankList[i].iata << stationaryVect[max_index]<< std::endl;
        stationaryVect[max_index] = -1;
    }
}

/**
 * Prints rank matrix for test proofing
*/

void PageRank::print_rankMatrix(){
    for(unsigned i = 0; i < n; i++){
        for(unsigned j = 0; j < n; j++){
            std::cout << rankMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

