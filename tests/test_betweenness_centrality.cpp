#include "../cs225/catch/catch.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

// add required header files to be tested 
#include "../graph.h"
using cs225_fp::Graph;

#include "../dijkstra.h"
using cs225_fp::Dijkstra;

#include "../betweenness_centrality.h"
using cs225_fp::BetweennessCentrality;

#include "../utility_functions.h"
using cs225_fp::float_equal;

TEST_CASE("Betweenness-Centrality correctly finds the importance values for all vertices", "[simple][connected]") {
    const double CONST_WEIGHT = 1;
    size_t num_vertices = 6;
    // undirected graph structure creating from using directed adjancy list idea
    // for the purposes of checking correct implementation of B/Wness-centrality 
    std::vector<std::pair<std::pair<size_t, size_t>, double>> edge_list =
    { 
        std::make_pair(std::make_pair(0, 1), CONST_WEIGHT),
        std::make_pair(std::make_pair(1, 0), CONST_WEIGHT), 

        std::make_pair(std::make_pair(1, 2), CONST_WEIGHT),
        std::make_pair(std::make_pair(2, 1), CONST_WEIGHT), 

        std::make_pair(std::make_pair(2, 3), CONST_WEIGHT),
        std::make_pair(std::make_pair(3, 2), CONST_WEIGHT), 

        std::make_pair(std::make_pair(3, 1), CONST_WEIGHT),
        std::make_pair(std::make_pair(1, 3), CONST_WEIGHT), 

        std::make_pair(std::make_pair(2, 5), CONST_WEIGHT),     // 1, 5
        std::make_pair(std::make_pair(5, 2), CONST_WEIGHT),     // 5, 1

        std::make_pair(std::make_pair(4, 5), CONST_WEIGHT),
        std::make_pair(std::make_pair(5, 4), CONST_WEIGHT), 

        std::make_pair(std::make_pair(0, 4), CONST_WEIGHT),
        std::make_pair(std::make_pair(4, 0), CONST_WEIGHT), 
    };
    Graph graph(num_vertices, edge_list);
    BetweennessCentrality BC_util(graph);
    BC_util.constructBetweennessCentrality(); 

    Dijkstra d(graph);

    std::vector<double> expected = {3.0, 5.0, 5.0, 0, 2, 3};
    

    REQUIRE(expected[0] == Approx(BC_util.getBetweennessCentrality(0)));
    REQUIRE(expected[1] == Approx(BC_util.getBetweennessCentrality(1)));
    REQUIRE(expected[2] == Approx(BC_util.getBetweennessCentrality(2)));
    REQUIRE(expected[3] == Approx(BC_util.getBetweennessCentrality(3)));
    REQUIRE(expected[4] == Approx(BC_util.getBetweennessCentrality(4)));
    REQUIRE(expected[5] == Approx(BC_util.getBetweennessCentrality(5)));

    // highest importance node this particular graph is vertex 1 or vertex 2 
    // bet since the functions queries the vector from left to right, it will be vertex 1
    bool actual = BC_util.getHighestImportanceVertex() == 1 || BC_util.getHighestImportanceVertex() == 2;
    REQUIRE (actual);

}