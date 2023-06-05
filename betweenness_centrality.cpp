/**
 * @file betweenness_centrality.cpp
 * Implementation of Betweenness-Certrality. 
 *
 * @author Ravi Patel 
 */

#include "betweenness_centrality.h"

#include <iterator>     // std::iterator 
#include <algorithm>    // std::sort
#include <iostream>

#include "dijkstra.h"
#include "utility_functions.h"

namespace cs225_fp {
BetweennessCentrality::BetweennessCentrality(const Graph& graph) : graph_(&graph) {
    betweenness_centralities_ = std::vector<double>(graph_->size(), 0);
}

void BetweennessCentrality::constructBetweennessCentrality(void) {
    size_t num_vertices = graph_->size();

    // dijkstra utility container (for calculating the shortest path and number of shortest path)
    Dijkstra dijkstra_util(*graph_);

    // for all vertices u, v in graph G 
    for (size_t u = 0; u < num_vertices; ++u) {
        for (size_t v = u+1; v < num_vertices; ++v) {
            // finds number of shortest paths from u to v 
            std::pair<size_t, double> shortest_path_util = dijkstra_util.getShortestPath(u, v);
            shortest_paths_counter_[u][v] = shortest_path_util; // number of shortest paths 

            // finds number of shortest paths from v to u (reverse direction)
            shortest_path_util = dijkstra_util.getShortestPath(v, u);
            shortest_paths_counter_[v][u] = shortest_path_util; 
            std::cout << "("<< u << "," << v << ")" << std::endl;
        }
    }

    for (size_t w = 0; w < num_vertices; ++w) {
        // checks for conditions where betweenness is zero, like when
        // - shortest path does not exist (disconnected vertex from graph)
        // - vertex for betweeness is either a source(only outgoing edges) or sink(only incoming edges) vertex
        if (graph_->disconnected(w) || graph_->source(w) || graph_->sink(w))
            continue;

        double btw_cent_value = 0;
        for (size_t u = 0; u < num_vertices; ++u) {
            for (size_t v = u+1; v < num_vertices; ++v) {
                if (u == w || v == w || shortest_paths_counter_[u][v].first == 0 || shortest_paths_counter_[v][u].first == 0 /* for disconnected nodes */)
                    continue;
                double shortest_paths_u_v = shortest_paths_counter_[u][v].first;

                double shortest_paths_u_w_v = 0;
                if (float_equal(shortest_paths_counter_[u][v].second, shortest_paths_counter_[u][w].second + shortest_paths_counter_[w][v].second))
                    shortest_paths_u_w_v = shortest_paths_counter_[u][w].first * shortest_paths_counter_[w][v].first;
                btw_cent_value += shortest_paths_u_w_v/shortest_paths_u_v;

                double shortest_paths_v_u = shortest_paths_counter_[v][u].first;

                double shortest_paths_v_w_u = 0;
                if (float_equal(shortest_paths_counter_[v][u].second, shortest_paths_counter_[v][w].second + shortest_paths_counter_[w][u].second)) 
                    shortest_paths_v_w_u = shortest_paths_counter_[v][w].first * shortest_paths_counter_[w][u].first;
                btw_cent_value += shortest_paths_v_w_u/shortest_paths_v_u;
            }
        }
        
        betweenness_centralities_[w] = btw_cent_value;
    }
}

size_t BetweennessCentrality::countShortestPaths(size_t source, size_t destination)  {
    return shortest_paths_counter_[source][destination].first;
    // return 0;
}

double BetweennessCentrality::getBetweennessCentrality(size_t vertex) {
    for (size_t i = 0; i < graph_->size(); ++i) {
        std::cout << shortest_paths_counter_[vertex][i].first << " ";
    }
    std::cout << std::endl;
    return betweenness_centralities_[vertex];
}

size_t BetweennessCentrality::getHighestImportanceVertex(void) const {
    size_t max_index = 0;
    double value = betweenness_centralities_[0];
    for (size_t i = 0; i < graph_->size(); ++i) {
        if (betweenness_centralities_[i] > value) {
            max_index = i;
            value = betweenness_centralities_[i];
        }
        std::cout << betweenness_centralities_[i] << " ";
    }
    std::cout << std::endl;
    
    return max_index;
}

std::pair<size_t, size_t> BetweennessCentrality::getMaxShortestPathsVerticesPair(void) {
    size_t source, dest;
    size_t count = 0;
    for (size_t u = 0; u < graph_->size(); ++u) {
        for (size_t v = u+1; v < graph_->size(); ++v) {
            if (count < shortest_paths_counter_[u][v].first) {
                count = shortest_paths_counter_[u][v].first;
                source = u;
                dest = v;
            }
            if (count < shortest_paths_counter_[v][u].first) {
                count = shortest_paths_counter_[v][u].first;
                source = v;
                dest = u;
            }
        }
    }
    return std::make_pair(source, dest);
}
}