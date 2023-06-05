/**
 * @file dijkstras.cpp
 * Implementation of Dijsktra's Algorithm (container class for executing shortest path). 
 *
 * @author Ravi Patel 
 */

#include "dijkstra.h"

#include <limits>   // DBL_MAX
#include <list>     // std::list     
#include <iostream> // std::cout, std::cerr, std::endl
#include <queue>    // std::queue

#include "graph.h"
#include "utility_functions.h"
#include "min_heap.h"

namespace cs225_fp {
Dijkstra::Dijkstra(const Graph& graph) : graph_(&graph) {
}

std::pair<size_t, double> Dijkstra::getShortestPath(size_t source_vertex, size_t dest_vertex) {    
    // improves the time-complexity by eliminating running dijkstras's for cases
    // when no incoming and/or outgoing edges for source and/or destination exist repectively 
    if (!graph_->exist(source_vertex) && !graph_->exist(dest_vertex))
        std::cerr << "ERROR: The source and/or destination vertex does not exist in the graph.";
    
    // a source vertex must have an outgoing edge to have shortest non-zero path to a destination
    // similarly a destination vertex must an incoming edge to have shortest non-zero path from a source
    if (graph_->getOutgoingEdgeCount(source_vertex) == 0 ||  graph_->getIncomingEdgeCount(dest_vertex) == 0) 
        return std::make_pair(0, DBL_MAX); // no shortest path exists 
    
    if (source_vertex == dest_vertex)
        return std::make_pair(0, 0);

    // -------------------------- Dijkstra's Algorithm -------------------------
    size_t num_vertices = graph_->size();
    
    // initilize vector for shortest distance from source vextex, initialized with an infinite value 
    std::vector<double> shortest_dist(num_vertices, DBL_MAX);

    // intialize vector for counting the number of equally weighted shortest paths 
    std::vector<size_t> paths(num_vertices, 0);

    // priority queue with key as vertices (indices of shortest_dist) from source vertex 
    // and value as destination vertex in [0, V)
    MinHeap* min_heap = new MinHeap(shortest_dist);

    shortest_dist[source_vertex] = 0; 
    min_heap->updateKey(source_vertex, shortest_dist[source_vertex]);
    ++paths[source_vertex];

    while(!min_heap->empty()) {
        std::pair<size_t, double> min_edge_util = min_heap->top();
        min_heap->pop();
        
        size_t current_node = min_edge_util.first;

        const std::list<std::pair<size_t, double>>* 
        incident_edges = graph_->incidentEdges(current_node);

        for (auto it = incident_edges->begin(); it != incident_edges->end(); ++it) {
            // destination vertex of the edge 
            size_t dest_node = (*it).first;
            double dest_weight = (*it).second;


            if (min_heap->hasKey(dest_node) 
            && !float_equal(shortest_dist[current_node], DBL_MAX))   // accounts for when a graph is connected 
            {   
                // std::cout << dest_node<< ": " << paths[dest_node] << std::endl;
                if (dest_weight + shortest_dist[current_node] < shortest_dist[dest_node]) {
                    shortest_dist[dest_node] = dest_weight + shortest_dist[current_node];
                    min_heap->updateKey(dest_node, shortest_dist[dest_node]);
                    paths[dest_node] = paths[current_node];
                }
                else if (float_equal(dest_weight + shortest_dist[current_node], shortest_dist[dest_node])) {
                    paths[dest_node] = paths[dest_node] + paths[current_node];
                }
                // std::cout << dest_node<< ": " << paths[dest_node] << std::endl << std::endl;
            }
        }
    }
    return std::make_pair(paths[dest_vertex], shortest_dist[dest_vertex]);   
}

}