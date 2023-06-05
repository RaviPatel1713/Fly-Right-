#pragma once 

#include <string>   // std::string 
#include <vector>   // std::vector 
#include <list>     // std::List (doubly linkedList)
#include <iterator> // std::iterator 
#include <utility>  // std::pair, std::make_pair 

namespace cs225_fp {
class Graph {
    public:
        /**
         * Default Constructor
         */
        Graph(void);

        /**
         * Constructs a adjacency list graph structure from specified file paths.
         * @param airport_data_filename the filepath for airport location data
         * @param route_data_filename the filepath for flight routes data 
         */
        Graph(const std::string &airport_data_filename, const std::string &route_data_filename);

        /**
         * Constructs a adjacency list graph structure from specified file paths with provided number of vertices. 
         * @param airport_data_filename the filepath for airport location data
         * @param route_data_filename the filepath for flight routes data 
         */
        Graph(const std::string &airport_data_filename, const std::string &route_data_filename, int size);

        /**
         * testing purposes: 
         * Constructs a adjacency list graph structure from provided edge list. 
         * @param adj_list 
         */
        Graph(size_t num_vertices, const std::vector<std::pair<std::pair<size_t, size_t>, double>>& directed_edge_list);              
        
        const std::list<std::pair<size_t, double>>* incidentEdges(size_t v) const;

        bool areAdjacent(size_t src, size_t dest);

        void printAirportDetails();

        std::vector<size_t>* BFS(size_t starting_vertex = 0) const;
                    
        // public utility functions for Adjacency List 
        bool empty(void) const;

        size_t size() const;

        /**
         * The functions checks whether a specified vertex key exists in the graph.
         * @param v the vertex key 
         * @return bool value for whether the key exists or not
         */
        bool exist(size_t v) const;

        size_t getIncomingEdgeCount(size_t v) const;

        size_t getOutgoingEdgeCount(size_t v) const;

        /**
         * The function checks whether a specified vertex is source vertex (only outgoing edges, no incoming).
         * @param v the vertex key 
         * @return bool value for whether the vertex is source or not
         */
        bool source(size_t v) const;

        /**
         * The function checks whether a specified vertex is sink vertex (only incoming edges, no outcoming).
         * @param v the vertex key 
         * @return bool value for whether the vertex is sink or not
         */
        bool sink(size_t v) const;

        /**
         * The function checks whether a specified vertex is edgeless(not incoming or outgoing edges) or not.
         * @param v the vertex key 
         * @return bool value for whether the vertex is edgeless or not
         */
        bool disconnected(size_t v) const;
    private:
        size_t num_vertices_;

        // each vertex element in the vector is LinkedList of a pair where the 
        // first value is the vertex and the second is weight from index vertex 
        // to destination vertex (in a directed manner )
        std::vector<std::list<std::pair<size_t, double>>> adj_list_;

        // each element in the vector holds an ordered pair of (latitude, longitude)
        std::vector<std::pair<double, double>> airport_locating_points_;

        // vector for keeping track of incoming edges of all vertices
        std::vector<size_t> incoming_edges_count_;

        // private helper functions 
        /**
         * The utility BFS function for traversing a single connected componentof a graph.
         * @param curr_vertex the starting vertex to start Breadth First Traversal 
         * @param visited the bool array representation to keep track of visited vertices in our traversal
         * @param vertex_traversal_list the vector representation to store the vertex traversal order 
         */
        void BFSUtil(size_t curr_vertex, std::vector<bool>& visited, std::vector<size_t>* vertex_traversal_list) const;
};
}