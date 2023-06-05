#pragma once 

#include <vector>   // std::vector
#include <map>      // std::map 

#include "dijkstra.h"

#include "graph.h"

namespace cs225_fp {
class BetweennessCentrality {
    public:
    BetweennessCentrality(const Graph& graph);

    /**
     * Cahches the number of shortest paths values between all possible pairs of vertices 
     * and stores in a map.
     * Computes the betweenness-centrality values for all the vertices.
     */
    void constructBetweennessCentrality(void);

    size_t countShortestPaths(size_t source, size_t destination);

    /**
     * Returns the vertex importance value from between-centrality.
     * @param vertex the specifide vertex for finding its importance in the graph
     * @return the quantified importance value of the vertex within the graph 
     */
    double getBetweennessCentrality(size_t vertex);

    /**
     * Returns the vertex with the highest importance in of its between-centrality. 
     * @return the vertex with the highest importance 
     */
    size_t getHighestImportanceVertex(void) const;

    /**
     * Returns the directed edge vertices pair (src, dest) with maximum number of shortest paths.
     * @return the vertices pair (src, dest)
     */
    std::pair<size_t, size_t> getMaxShortestPathsVerticesPair(void);

    const std::vector<double>* getSortedOrderBetweennessCentrality() const;

    private:
    // nested map to associate the total number of shortest paths from a source vertex 
    // which is the outermost map to destination vertex which is the innermost map
    std::map<size_t, std::map<size_t, std::pair<size_t, double>>> shortest_paths_counter_;

    // vector to keep track of calculated betweenness-centrality of each vertex 
    std::vector<double> betweenness_centralities_;    

    // non-owning pointer to specified ajacency list graph structure
    const Graph* graph_;
};
}