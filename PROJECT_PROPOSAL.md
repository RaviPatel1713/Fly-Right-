# Project Proposal 

### **Our dataset and what we are trying to solve:**

We will be working with the openFlights dataset for our final project, an open-source dataset containing flights routes and airports. Since we will be exclusively using the airport dataset containing latitude and longitude, the graph will be interpreted as an undirected graph with the weight as the distance (in km) between individual airports. We plan to extract data airports use to compute the shortest connecting path between source and destination airports. We also expect to gain insights on how individual nodes influence the flow of flight routes by finding the airport of most importance in terms of the number of times it lies in the shortest path between other nodes. By completing this project, we expect to understand the applications of graph algorithms in real-world flight route-planning for customer convenience, comfort, and/or affordability.

### **Dataset acquisition and Processing:**

The OpenFlights dataset is given in the CS225 example datasets. The dataset contains over 10,000 airports, train stations, and ferry terminals from the world’s most connecting cities/regions.

First, we will download the dataset in raw data form and store it in a .dat file in our master repository from the OpenFlights website. We will then use the Python CSV module or pandas library to convert the raw data into CSV format within the repository.

Each of the data points is organized in the following format:

*507,"London Heathrow Airport","London","United Kingdom", "LHR", "EGLL", 51.4706, -0.461941, 83, 0,m"E", "Europe/London", "airport", "OurAirports"*

The sub-entries in a data point include:

-   **Airport ID**
    
-   **Name of airport** (to whom the data point belong to)
    
-   **City** (served by the airport)
    
-   **Country or territory** (where the airport is located)
    
-   IATA code (3-letter code, NULL -> if unknown or unspecified)
    
-   ICAO code (4-letter code, NULL -> if unknown or unspecified)
    
-   **Latitude** (measured in degrees with at most 6-sig figs, Negative -> South, Positive -> North)
    
-   **Longitude** (measured in degrees with at most 6-sig figs, Negative -> West, Positive -> East)
    
-   Altitude (measured in ft)
    
-   Timezone (hours offset from Universal Time Zone)
    
-   Daylight Savings Time (One of E (Europe), A (US/Canada), S (South America), O (Australia), Z (New Zealand), N (None) or U (Unknown))
    
-   TZ database timezone (the Olsen convention naming format using continent and city names)
    
-   Type (since the OpenFlights dataset also contains ferries, train stations along with airports, the type is used to specify whether a datapoint represents an airport)
    
-   Source (the origin/contribution source of the data, whether “OurAirports” or “Legacy” for resourceful data or old resourceful data respectively or user added data, which is from an unverified user)

To create a weighted graph from the dataset, we will use all the bold marked sub-entries. Although it would have also been necessary for us to use the last two sub-entries, Type and Source, for extracting only the verified airport dataset, we will not use that information because the OpenFlights database already provides a separate dataset (*airports.dat*) for that with high quality.

We will have an undirected graph with weight as the distance between individual airports in kilometers. We will establish a connection from each airport node to every other airport node with their respective weight distance calculated using their latitude and longitude.

> Important
The formula to calculate the distance between two locating points (having latitude and longitude) of a globe is called the Haversine Formula.
[Haversine formula - Wikipediahttps://en.wikipedia.org › wiki › Haversine_formula](https://en.wikipedia.org/wiki/Haversine_formula)

#### Graph Representation

The total number of edges in our undirected graph will be (n * (n-1))/2, which will make our graph a maximally dense graph.

In the Big-O analysis, O(e) = O(v^2), where e is the number of edges and v is the number of vertices in our graph.

Hence, it is more efficient in space complexity to store a dense undirected graph in an adjacency matrix (as opposed to an adjacency list that holds all indecent edges in a linked structure).

The airport ID conveniently increasingly starts from 1 with all unique IDs, which can be used as adjacency matrix indices for our graph representation. We plan to create a hashing structure for mapping the airport identification information, the airport name to the unique ID. The matrix nodes will be represented as airport IDs, and the edges defined by distance will be calculated and represented as the matrix elements.

    For example, suppose our graph is called G,
	(for dense graph where there is an edge between every i and j with i not equal to j)
	    
	    G[i][j] = distance calculated between node i and node j (using Haversine Formula)

### **Graph Algorithms:**

*Graph traversal (BFS, DFS):* In our final project, we will use Breadth First Search traversal algorithm for both shortest path and betweenness centrality algorithms. Although BFS will have higher space complexity, BFS always finds the shortest path first, unlike DFS which uses depth first approach (which might be very time consuming in cases of very big graph sizes). The runtime for DFS is going to be O(E + V) when using the adjacency list and O(V^2) when using the adjacency matrix.

*Shortest Path Algorithm (Dijkstra's):* Since we are going to be working with a weighted graph, we will be using Dijkstra’s Algorithm to find the shortest path in terms of time taken to get from point A to point B. In graph weights is going to be the distance between point A and point B. The runtime of this algorithm is going to be O(V lg V + E lg V) where V represents the number of nodes (or vertices) and E represents the number of edges assuming a connected graph.

*Betweenness Centrality Algorithm:* We will use the betweenness centrality algorithm to a number of different possibilities. The centrality algorithm will help us determine the most significant airport connecting the entire graph and we will use this information to direct our flights through that specific airport. The runtime of this algorithm si going to be O(V x E + E2 x log(V)) and O(V + E) space complexity, where V, E are the number of vertices and edges in a graph, respectively.

### **General timeline:**

November 29: Finish proposal and contract

November 30: Finish downloading the data, processing the data on Python, and converting the data into an adjacency matrix

December 3: Finish implementing our first graph traversal (BFS and DFS) in preparation to implement Dijkastra’s algorithm

December 6: Finish implementing Dijkastra’s algorithm in our code base

December 11: Finish implementing the betweenness centrality algorithm in our code base

December 12: Make sure our codebase is fully functional and can be used in a variety of datasets

December 13: Make sure our final project video and all other deliverables are complete

