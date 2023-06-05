
# Flight Route Planning with Graph Algorithms

Final Project Video Link: https://youtu.be/K1nZ3DdwI8g


This repository contains the code and data for a project focused on flight route planning using graph algorithms. The project utilizes the openFlights dataset, which provides information on airports and flight routes.

## Dataset

The dataset used in this project is the openFlights dataset, an open-source collection of flight routes and airport information. Specifically, we are working with the airport dataset, which includes details such as airport names, locations (latitude and longitude), and other relevant attributes. The dataset is stored in CSV format.

## Problem Statement

The main objective of this project is to utilize graph algorithms to address flight route planning challenges. The specific goals are as follows:

1. **Shortest Path:** Find the shortest connecting path between a given source and destination airport. The distance between airports is calculated based on their latitude and longitude coordinates.

2. **Airport Importance:** Identify key airports that significantly influence the flow of flight routes. This is determined by examining the airports that frequently appear in the shortest paths between other nodes.

The insights gained from this analysis can help improve flight route planning in terms of customer convenience, comfort, and affordability.

## Implementation

### Dataset Processing

To process the openFlights dataset, we have provided Python code that converts the raw data into CSV format. The code uses either the CSV module or the pandas library to perform the conversion.

### Graph Representation

The dataset is interpreted as an undirected graph, where airports serve as nodes and the distance between them represents the edge weight. We use an adjacency matrix to store the graph, as it offers more efficient space complexity for a dense graph like ours. The matrix elements represent the distances between airports, calculated using the Haversine formula.

### Graph Algorithms

The project utilizes the following graph algorithms:

1. **Breadth-First Search (BFS) and Depth-First Search (DFS) Traversal:** BFS is used to find the shortest path between airports, as it guarantees efficient discovery of the shortest path. DFS is also implemented for comparison purposes, but it may be slower for larger graphs.

2. **Dijkstra's Algorithm:** This algorithm is employed to find the shortest path between airports, considering the distance as the weight. Dijkstra's Algorithm provides an efficient solution for weighted graphs.

3. **Betweenness Centrality:** The betweenness centrality algorithm is applied to identify the most significant airports in terms of their influence on the overall connectivity of the graph. This information can be valuable for flight route planning.

## Usage

1. Clone the repository:

   ```shell
   git clone https://github.com/your-username/flight-route-planning.git
   ```

2. Download the openFlights dataset from the CS225 example datasets or from the OpenFlights website.

3. Process the dataset by running the provided Python code for data conversion.

4. Run the main code files to perform graph traversal, find shortest paths, and calculate betweenness centrality.

5. Modify and adapt the code as needed for your specific requirements and use cases.

## Timeline

- November 8: Finish proposal and contract
- November 30: Download and process the dataset into an adjacency matrix
- December 3: Implement BFS and DFS traversal algorithms
- December 6: Implement Dijkstra's Algorithm
- December 11: Implement betweenness centrality algorithm
- December 12: Ensure codebase functionality and compatibility with various datasets
- December 13: Finalize project deliverables and documentation

## Contributors

- John Doe: john@example.com
- Jane Smith: jane@example.com

Please feel free to contribute to this project by creating pull requests or raising issues for bug fixes or enhancements.

**Note:** This project was developed as part of a final project for [Course Name/Number]
