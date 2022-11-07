# Project Proposal:

## Leading Question

Would we be able to develop a tool to find the shortest path between two airports given their names using the OpenFlights Airport Dataset.

## Dataset Acquisition
We are going to be using the openflight dataset (https://openflights.org/data.html).

## Data Format
We will be using the airport ID's, names, countries, latitdue, and longitude. Id's and names will be used for mapping vertex's and allowing for cleaner formatting. Countries will be used if we need to scale down size of data set. Latitude and longitude will be used for mapping weights on edges.

The parameters of different fields of our data are outlined beloew:
Airport ID-  Unsigned Integer Unique OpenFlights identifier for this airport. 

Name- 	Name of airport. May or may not contain the City name. String.

City- 	Main city served by airport. May be spelled differently from Name. String.

Country- 	Country or territory where airport is located. See Countries to cross-reference to ISO 3166-1 codes. String.

IATA- 	3-letter IATA code. Null if not assigned/unknown.

ICAO- 	4-letter ICAO code. Null if not assigned.

Latitude- 	Decimal degrees, usually to six significant digits. Negative is South, positive is North.

Longitude- 	Decimal degrees, usually to six significant digits. Negative is West, positive is East.

Altitude- 	In feet.

Timezone- 	Hours offset from UTC. Fractional hours are expressed as decimals, eg. India is 5.5.

DST- 	Daylight savings time. One of E (Europe), A (US/Canada), S (South America), O (Australia), Z (New Zealand), N (None) or U (Unknown). See also: Help: Time

Tz database time zone- 	Timezone in "tz" (Olson) format, eg. "America/Los_Angeles".

Type- 	Type of the airport. Value "airport" for air terminals, "station" for train stations, "port" for ferry terminals and "unknown" if not known. In airports.csv, only type=airport is included.

Source- 	Source of this data. "OurAirports" for data sourced from OurAirports, "Legacy" for old data not matched to OurAirports (mostly DAFIF), "User" for unverified user contributions. In airports.csv, only source=OurAirports is included.

## Data Correction
Some of the fields of data may have been mis-typed and might contain negative values or non-numeric values for unsigned data. This should be converted into positive numeric data (integer or decimal based on the data field) or should be entirely removed if not salvageable. If the airport is not written into the field, it should be labeled as "Unknown Airport 1", "Unknown Airport 2" etc.


## Data Storage


A map with key-value structure where keys are a string that contains the airport name of our nodes and values are integers that represent the number of our node.
A map with key-value structure where keys are a string that contains the airport name of our nodes and values that is a pair that stores the longitude and latitude of the airport.
We will store our graph in an adjacency matrix which is implemented by a 2 dimensional vector containing ungsigned integers where the indices of our vector represent the 2 nodes connected by the edge and the value of the 2d vector at the specified indices represent the weight and presence of an edge. A non-zero value shows that an edge is present with the specified weight.

## Algorithm 

### Breadth First Search (BFS)
The Breadth First Search Algorithm is a graph traversal algorithm that can be used for searching for a node in the graph.

Input: 
    1. A simple graph on which we want to perform search on.
    2. The start node from which should be an unsigned integer.
    3. The target node which should be an unsigned integer.

Output: A boolean representing whether there is a path to the target node from the start node or not.

Runtime: O(n) where n is the number of nodes.

### Dijkstra's Algorithm

Dijkstra's algorithm is an algorithm for finding the shortest paths from a specified node to all other nodes in a graph.

Input:
    1. A simple graph on which we want to perform the function on.
    2. The start node from which you want to return distances to all other nodes.

Output: A vector of unsigned integers where each index represents the distance from the start node to the corresponding node. The index representing the start node should have the value 0.

Runtime: O(n*log(n)) where n is the number of nodes in the graph.

### A* search

Using the diagonal distance heuristic using latitude and longitude which si O(1) time runtime.

Input:
    1. A simple graph on which we want to perform search on.
    2. The start node from which should be an unsigned integer.
    3. The target node which should be an unsigned integer.

Output: A vector of ints representing the order of nodes traveresed to reach the target node from the start node.

Runtime: The runtime of A* is O(n) where n is the number of nodes in the graph.

## Timeline
Week 1: 11/7-11/13 : Parse and organize and correct data if needed.


Week 2: 11/14-11/20 : Convert data into graph and Implement BFS Traversal


Week 3: 11/21-11/27 (Fall Break) : A* Search and Dijktras Algorithm implementation


Week 4-4.5: 11/28-12/8 : Finishing remaining implementation and extensive testing. Finish report and prepare presentation.