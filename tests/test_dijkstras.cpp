
#include "../cs225/catch/catch.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include<utility>
#include <limits> // DBL_MAX

#include "../graph.h"
using cs225_fp::Graph;

#include "../dijkstra.h"
using cs225_fp::Dijkstra;

#include "../utility_functions.h"
using cs225_fp::float_equal;
using cs225_fp::DBL_MAX;

Graph* create_graph_G1() {
    size_t num_vertices = 6;
    std::vector<std::pair<std::pair<size_t, size_t>, double>> edge_list =
    { 
        std::make_pair(std::make_pair(0, 1), 18), 
        std::make_pair(std::make_pair(0, 3), 11), 
        std::make_pair(std::make_pair(0, 4), 3), 
        std::make_pair(std::make_pair(2, 0), 22), 
        std::make_pair(std::make_pair(2, 3), 8), 
        std::make_pair(std::make_pair(3, 0), 50),
        std::make_pair(std::make_pair(3, 1), 1), 
        std::make_pair(std::make_pair(3, 2), 2),
        std::make_pair(std::make_pair(3, 5), 10),
        std::make_pair(std::make_pair(4, 3), 7),
        std::make_pair(std::make_pair(5, 0), 17),
        std::make_pair(std::make_pair(5, 2), 77),
    };
    return new Graph(num_vertices, edge_list);
}

Graph* create_graph_G2() {
    size_t num_vertices = 6;
    // non-cyclic linkedlist-like graph structure
    std::vector<std::pair<std::pair<size_t, size_t>, double>> edge_list =
    { 
        std::make_pair(std::make_pair(0, 1), 10), 
        std::make_pair(std::make_pair(1, 2), 20), 
        std::make_pair(std::make_pair(2, 3), 30), 
        std::make_pair(std::make_pair(3, 4), 40), 
        std::make_pair(std::make_pair(4, 5), 50)
    };
    return new Graph(num_vertices, edge_list);
}

Graph* create_graph_G3() {
    return new Graph(5, std::vector<std::pair<std::pair<size_t, size_t>, double>>());
}

Graph* create_graph_G4() {
    size_t num_vertices = 6;
    // non-cyclic linkedlist-like graph structure
    std::vector<std::pair<std::pair<size_t, size_t>, double>> edge_list =
    { 
        std::make_pair(std::make_pair(0, 1), 7), 
        std::make_pair(std::make_pair(0, 2), 3), 
        std::make_pair(std::make_pair(2, 4), 2), 
        std::make_pair(std::make_pair(4, 1), 2), 
        std::make_pair(std::make_pair(2, 0), 10), 
        std::make_pair(std::make_pair(2, 3), 17),
        std::make_pair(std::make_pair(4, 5), 13), 
        std::make_pair(std::make_pair(5, 3), 2), 
    };
    return new Graph(num_vertices, edge_list);
}

TEST_CASE ("Dijkstra's algorithm finds the correct shortest path distance for cyclic simple connected graph") {
    Graph* G1 = create_graph_G1();
    Dijkstra dijkstra_container(*G1);
    
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(0, 3).second, 10.0) );
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(3, 0).second, 24.0) );
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(0, 1).second, 11.0) );
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(1, 0).second,  std::numeric_limits<double>::max()) );
    delete G1;
}

TEST_CASE ("Dijkstra's algorithm finds the correct shortest path distance for non-cyclic simple connected graph") {
    Graph* G2 = create_graph_G2();
    Dijkstra dijkstra_container(*G2);
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(0, 1).second, 10.0) );
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(1, 2).second, 20.0) );
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(2, 3).second, 30.0) );
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(3, 4).second, 40.0) );
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(4, 5).second, 50.0) );
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(0, 5).second, 150.0) );

    REQUIRE ( float_equal(dijkstra_container.getShortestPath(1, 0).second, DBL_MAX) );
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(2, 1).second, DBL_MAX) );
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(3, 2).second, DBL_MAX) );
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(4, 3).second, DBL_MAX) );
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(5, 4).second, DBL_MAX) );
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(5, 0).second, DBL_MAX) );
    delete G2;
}

TEST_CASE ("Dijkstra's algorithm finds the correct shortest path distance for edgeless disconnected graph") {
    Graph* G3 = create_graph_G3();
    Dijkstra dijkstra_container(*G3); // complete edgeless 5 vertices graph 
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(0, 1).second, DBL_MAX) );
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(1, 2).second, DBL_MAX) );
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(2, 3).second, DBL_MAX) );
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(3, 4).second, DBL_MAX) );
    delete G3;
}

TEST_CASE ("Dijkstra's algorithm finds the correct shortest path distance for multiple-shortest-path connected graph", "[multiple-shortest-path][connected]") {
    Graph* G4 = create_graph_G4();
    Dijkstra dijkstra_container(*G4); 
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(0, 1).second, 7.0) );
    REQUIRE ( dijkstra_container.getShortestPath(0, 1).first == 2 ); // two different shortest path 
    REQUIRE ( float_equal(dijkstra_container.getShortestPath(2, 3).second, 17.0) );
    REQUIRE ( dijkstra_container.getShortestPath(2, 3).first == 2 );
    delete G4;
}


