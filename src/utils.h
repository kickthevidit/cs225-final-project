#pragma once
#include <utility>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cassert>
#include <fstream>
#include <unordered_map>
#include <utility>

#include "airport.h"

#include <list>
#include <memory>


typedef std::vector<std::vector<double>> AdjMatrix;
typedef std::list<Airport*> AirportList;
typedef std::map<int, Airport *> AirportMap;
typedef std::map<std::string, int> CodeToNodeMap;
typedef std::vector<std::vector<std::string>> V2D;

/**
 * Takes a filename and reads in all the text from the file
 * Newline characters are also just characters in ASCII
 * 
 * @param filename The name of the file that will fill the string
 * @return A string containing the whole text of the given file
 */
std::string file_to_string(const std::string & filename);

/**
* Functions for the removal of whitespace to the left or right of a string (or both)
*
* @param str The string being processed
* @return The processed string
*/
std::string TrimRight(const std::string & str);
std::string TrimLeft(const std::string & str);
std::string Trim(const std::string & str);
// std::string TrimQuote(std::string & str);

/**
 * Given a string and character, split the string by the character and store in a vector
 * A 'split' string treats the character as a breakpoint and creates a separate item
 * in the output vector for each substring. 
 * 
 * NOTE: The separator character is not included in the substrings.
 * 
 * The total number of substrings created (the length of fields) is returned 
 *  
 * @param str1 The string being split
 * @param sep The separator character
 * @param fields The string vector storing all substrings created by the split
 * @return The number of substrings created
 */
int SplitString(const std::string & str1, char sep, std::vector<std::string> &fields);

/**
* Input: file path as string
* Processing: takes content of file and organises it into a 2 dim vector splitting using whitespaces and newline characters
* Output: a 2d vector
*/
V2D fileToV2D(const std::string& filename);

/**
 * Processing our datasets from 2d vector form to an adjacency matrix and a map with key-value pairs IATA number-Airport.
*/
void createDatasets(AirportMap &airport_mapSource, AirportMap &airport_mapID, CodeToNodeMap& nodeMap, AdjMatrix &adj, const V2D &airports, const V2D& routes);

/**
* Input: latitude-longitude of 2 locations
* Output: the distance between the two locations using Haversine Formula
*/
double CalculateDist(double long1, double lat1, double long2, double lat2);

/**
*  Given a 2d vector of adjacency matrix print it out 
*/
void PrintAdjMatrix(const AdjMatrix &adj, unsigned range = 10);

/**
*  Write part of an adjacency matrix of size n*n onto a file with specified file path. 
* */
void PrintAdjMatrix(const AdjMatrix &adj, std::string file_name = "adjacency-matrix.txt", unsigned range = 10);
