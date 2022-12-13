#include "PageRank.h"

/**
 * Constructs Markov Matrix from graph
*/
PageRank::PageRank(const std::vector<std::vector<double>> &adjMatrix){
    //copy adj matrix, we can uses weights to determine if route exist
    rankMatrix = adjMatrix;
    n = rankMatrix.size();
    for(unsigned i = 0; i < n; i++){
        double connectionCount = 0; //count the degree of node. I.E summing row
        for(unsigned j = 0; j < n; j++){
            if(rankMatrix[i][j] <= 0){ 
                rankMatrix[i][j] = 0;
 
            }
            else{
                rankMatrix[i][j] = 1; //replace weight with 1
                connectionCount++;
            }
        }
        //Divide by zero case, gets filled with 1/n
        if(connectionCount == 0){
            for(unsigned j = 0; j < n; j++){
                rankMatrix[i][j] = 1 / double(n);
            }
        }
        else{
            for(unsigned j = 0; j < n; j++){
                if (rankMatrix[i][j] != 0)
                    rankMatrix[i][j] = rankMatrix[i][j] / connectionCount;
            }
        }
    }
}

/**
 * Returns stationary vector of airport ranks via power iteration
*/
std::vector<double> PageRank::genStationaryVect(){
    std::vector<double> vect(n);

    //intialize arbitratry vect
    for(double& val : vect){
        val = 1/double(n);
    }

    double prevVal = 0;
    
    do{
        prevVal = vect[0]; //update prev val
        std::vector<double> copyVect = vect;
        for(unsigned i = 0; i < n; i++){
            double sum = 0;
            //matrix vector multiplication
            for(unsigned j = 0; j < n; j++){
                sum += rankMatrix[j][i] * double(copyVect[j]);
            }
            vect[i] = sum;
        }
        //check if vect is stationary (may need change based on data set size)
    }   while(!(std::abs(vect[0] - prevVal) < 0.000001));
    return vect;
}

/**
 * Prints sorted vector of Airport ranks
*/
void PageRank::print_rankVect(const std::map<int, Airport *>& AirportMap){
    std::vector<double> stationaryVect = genStationaryVect();
    std::vector<Airport> rankList;

    for(unsigned i = 0; i < 25; i++){
        //find index of max rank
        int max_index = std::distance(stationaryVect.begin(), std::max_element(stationaryVect.begin(), stationaryVect.end()));
        rankList.push_back(*(AirportMap.at(max_index)));
        std::cout << i+1 << ":" << rankList[i].iata << " " << stationaryVect[max_index]<< std::endl;
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


std::vector<std::vector<double>> PageRank::getMatrix(){
    return this->rankMatrix;
}
