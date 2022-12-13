# BFS
First, we made a Breadth First Search, following the general algorithm from class. In this function, the input is the ID's of a start and end airport and a 2D vector representing out adjacency matrix. The return is a bool as to whether these two airports were connected or not. It uses a queue to determine the order of nodes checked and a set that holds all the previously visited nodes. The run time of out BFS is O(m+n). For testing, we would make sample 2D vectors following the pattern of our adjacency matrix and see that all the pair of points that were connected returned true and the ones that that weren't returned false. 

# Dijkstra's
Our Dijkstra's was used to find the shortest path between two airports. The function takes in a 2D vector representing our adjacency matrix, and two integers, representing the ID's of the designated start and end airports. The function returns a vector of integers signifying the path of airports to get from the start and end. We use 3 vectors: a vector of doubles (dist) to keep track of the shortest path from the source to each node, a vector of bools (sptSet) to keep track if each node has been visited yet, and another vector of ints (parents) to keep track of the index of the parent of each node in this traversal. We set all the values in dist to be the max integer except the source and similarly all the values in sptSet to be false. From there, we use a queue in a BFS style to traverse the adjacency list and adjust dist and parents as soon as shorter distances from the source to that node have been found. The runtime of Dijkstra's in this case should be O(V*log(V) + E) where V is the number of vertices and E is edges. For testing, we again made model adjacency matrices and saw that given any two inputs, the function would return the shortest path between them or handle extraneous test cases accordingly. 


# Page Rank
Page Rank is an algorithm used to rank verticies in a graph based on a chosen metric that can written as a probability. In our case we have airports and routes so naturaly Page Rank fits answersing the importance of an airport based on a connectivity rank. To Implement Page Rank we created a 2D adjacency matrix with 1 representing a route between two airports and 0 meaning a route does not exist. From here we uses a Linear Algebra approach to optaining ranks. The first step is normalizing the mastrix so that all entries in row (typically columns) sum to 1. We also accounted for the case of a row summing to zero and chose 1 / number of airports. This step is crucial as the next step involves multiplying our Markov matrix with an arbitray vector until it converges and a zero row will converges to zero. The next step involved creating a sorted vector of ranks and mapping the index to an airport.

Our results are as following (Top 5 U.S. only):
```
1:ATL 0.0278308
2:DEN 0.0266028
3:ORD 0.0263771
4:DFW 0.0245205
5:MSP 0.0210302
```

We found our results to match our assumptions very well, however ran into issues when increasing the number of airports. To generate our stationary vector it takes O(V * E) = O(n^2) time on reasonable scales. However, as the number of airports increases our constant becomes more significant and atributes to a worse case runtime of O(n^3). This is cuased from generating our stationary vector as it gains accuracy with more iterations.

To test our Page Rank algorithm we used a Markov Matrix homework from UIUC's MATH 257 to see if the Markov matrix and stationary vector matched our implementation. The code is as follows

Test 1 Image (no zero vectors included):
https://user-images.githubusercontent.com/112449185/207220395-05ec5c80-101c-4a45-bf9a-d1ba7b8ed3b7.png"

Test 2 Image (zero vectors included):
"https://user-images.githubusercontent.com/112449185/207220419-995feb38-90ee-442a-a9a2-1e2f04d90c01.png"

Possible improvements: Decreasing sparsity of matrix will help keep constant minimal

# Leading Questions
Our project adequately addressed our guiding questions. For the first question, we developed a method using Dijkstra's to find the most optimal route to travel between two airports with the lowest distance travelled. 
In regards to our second question, we developed a Page Rank function to rank airports analyze the importance of an airport which was guided by airport connectivity.
