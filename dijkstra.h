#pragma once 

#include <utility> //   std::pair 

#include "graph.h"

namespace cs225_fp {
    class Dijkstra {
        public:
            Dijkstra(const Graph& graph);
            std::pair<size_t, double> getShortestPath(size_t source_vertex, size_t dest_vertex);
        private:
            const Graph* graph_;
    };
}