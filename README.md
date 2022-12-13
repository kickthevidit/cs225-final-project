# CS225 Final Project
Members: Ryan Forester, Vidit Gautam, Chris Wang, and Braden Nigg

## Deliverables

README.md, Results.md - Github Repository

Video submission - Github Repository, Youtube

## Project Description

Our project is based on interpreting the [Openflight](https://openflights.org/data.html) Dataset. This data set contains a large amount of data about airports and routes around the world. This led our group to design two primary functions. The first finds the shortest path using Dijkstra's A which given a start and end location will give a path a distance. The second function is a Page Rank function that analyzes the importance of airports and gives a ranking.

## Getting Started

To use our project, copy and paste the following command into your terminal:

```
git clone https://github.com/kickthevidit/cs225-final-project.git
```

Next you will need to make sure your terminal is in the final project directory and copy the following lines:

```
mkdir build
cd build
cmake ..
```

Remaining in the build directory you can now run our program using:

To Compile code:

```
make
```

To run program:

```
./main <airport1_IATA> <airport2_IATA>
```

To run tests:
```
./test
```
## Example Output

```
Args: MSO,CMI
Reading Datasets...
Getting node IDs...
Creating Adjacency Matrix...
See Adjacency Matrix in adjacency-matrix-500.txt
Conducting BFS...

Possible path found
Conducting Dijkstra's...

Result Path: 548        306     256     513
Conducting PageRank...
1:ATL 0.0278308
2:DEN 0.0266028
3:ORD 0.0263771
4:DFW 0.0245205
5:MSP 0.0210302
6:DTW 0.0207955
7:LAS 0.0204485
8:CLT 0.0194942
9:IAH 0.0179819
10:PHL 0.0155464
11:SLC 0.0152736
12:LAX 0.0152569
13:DCA 0.0149785
14:IAD 0.0139954
15:PHX 0.0139847
16:SEA 0.0135744
17:MCO 0.0134157
18:EWR 0.0128854
19:BOS 0.0127987
20:SFO 0.0127728
21:BWI 0.012348
22:MDW 0.0121322
23:LGA 0.0115348
24:JFK 0.0112625
25:TPA 0.0110122
```
