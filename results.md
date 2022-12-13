# BFS
First, we made a Breadth First Search, following the general algorithm from class. In this function, the input is the ID's of a start and end airport and a 2D vector representing out adjacency matrix. The return is a bool as to whether these two airports were connected or not. It uses a queue to determine the order of nodes checked and a set that holds all the previously visited nodes. The run time of out BFS is O(m+n). For testing, we would make sample 2D vectors following the pattern of our adjacency matrix and see that all the pair of points that were connected returned true and the ones that that weren't returned false. 

# Dijkstra's
Our Dijkstra's was used to find the shortest path between two airports. The function takes in a 2D vector representing our adjacency matrix, and two integers, representing the ID's of the designated start and end airports. The function returns a vector of integers signifying the path of airports to get from the start and end. We use 3 vectors: a vector of ints (dist) to keep track of the shortest path from the source to each node, a vector of bools (sptSet) to keep track if each node has been visited yet, and another vector of ints (parents) to keep track of the index of the parent of each node in this traversal. We set all the values in dist to be the max integer except the source and similarly all the values in sptSet to be false. From there, we iteratively traverse the adjacency list and adjust dist and parents as soon as shorter distances from the source to that node have been found. The runtime of Dijkstra's in this case should be O(V * log(V)) where V is the number of vertices.


# Page Rank
s
