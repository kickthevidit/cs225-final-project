#pragma once

#include "airport.h"
#include "utils.h"


#include <vector>
#include <memory>
#include <utility>


typedef std::vector<std::vector<double>> AdjMatrix;
typedef std::vector<Airport*> AirportList;

void ProcessAirports(AirportList &airports, const V2D & airports_dataset);

AdjMatrix ProcessAdjacencyMatrix(AirportList &airports, const V2D &routes_dataset);

double CalculateDist(double long1, double lat1, double long2, double lat2);