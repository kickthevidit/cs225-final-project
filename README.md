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

