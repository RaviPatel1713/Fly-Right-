#include "../cs225/catch/catch.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

// add required header files to be tested 
#include "../graph.h"
using cs225_fp::Graph;

#include "../utility_functions.h"
using cs225_fp::float_equal;

/**
 * This test suite is designed only to test the methods and functionalities of the adjacency list 
 * graph implementation ONCE it has been loaded from the dataset. 
 */

// TEST_CASE("Graph implementation correctly reads data from the specified filepaths") {
//     std::string DEFAULT_AIRPORT_DATA_FILEPATH = "dataset/airports_refined.csv";
//     std::string DEFAULT_ROUTE_DATA_FILEPATH = "dataset/routes_refined.csv";
// }

TEST_CASE("Graph correctly implements vertices in the adjancecy list") {
    // graph with 5 vertices {0, 1, 2, 3, 4}
    size_t num_vertices = 5;
    std::vector<std::pair<std::pair<size_t, size_t>, double>> edge_list =
    { std::make_pair(std::make_pair(0, 1), NULL), 
      std::make_pair(std::make_pair(0, 2), NULL), 
      std::make_pair(std::make_pair(1, 3), NULL), 
      std::make_pair(std::make_pair(3, 0), NULL), 
      std::make_pair(std::make_pair(2, 3), NULL), 
      std::make_pair(std::make_pair(2, 4), NULL), 
      std::make_pair(std::make_pair(4, 3), NULL) };
    Graph graph(num_vertices, edge_list);
    
    for (size_t i = 0; i < num_vertices; ++i) 
        REQUIRE( graph.exist(i) );
}

TEST_CASE("Graph has correct number of vertices and logic works on empty graph") {
    // graph with 5 vertices {0, 1, 2, 3, 4}
    size_t num_vertices = 5;
    std::vector<std::pair<std::pair<size_t, size_t>, double>> edge_list =
    { std::make_pair(std::make_pair(0, 1), NULL), 
      std::make_pair(std::make_pair(0, 2), NULL), 
      std::make_pair(std::make_pair(1, 3), NULL), 
      std::make_pair(std::make_pair(3, 0), NULL), 
      std::make_pair(std::make_pair(2, 3), NULL), 
      std::make_pair(std::make_pair(2, 4), NULL), 
      std::make_pair(std::make_pair(4, 3), NULL)
    };
    Graph graph(num_vertices, edge_list);
    REQUIRE( graph.size() == num_vertices );

    Graph empty_graph(0, std::vector<std::pair<std::pair<size_t, size_t>, double>>());
    REQUIRE( empty_graph.size() == 0 );
}

TEST_CASE("Graph implementation correctly finds number of incident edges") {
    // graph with 5 vertices {0, 1, 2, 3, 4}
    size_t num_vertices = 5;
    std::vector<std::pair<std::pair<size_t, size_t>, double>> edge_list =
    { std::make_pair(std::make_pair(0, 1), NULL), 
      std::make_pair(std::make_pair(0, 2), NULL), 
      std::make_pair(std::make_pair(1, 3), NULL), 
      std::make_pair(std::make_pair(3, 0), NULL), 
      std::make_pair(std::make_pair(2, 3), NULL), 
      std::make_pair(std::make_pair(2, 4), NULL), 
      std::make_pair(std::make_pair(4, 3), NULL)
    };
    Graph graph(num_vertices, edge_list);

    std::vector<size_t> expected_incident_edge_count = {2, 1, 2, 1, 1};
    
    for (size_t i = 0; i < num_vertices; ++i) 
        REQUIRE( graph.getOutgoingEdgeCount(i) == expected_incident_edge_count[i] );
}

TEST_CASE("Graph implementation correctly finds correct vertex values of indcident edges") {
    // graph with 5 vertices {0, 1, 2, 3, 4}
    size_t num_vertices = 5;
    std::vector<std::pair<std::pair<size_t, size_t>, double>> edge_list =
    { std::make_pair(std::make_pair(0, 1), NULL), 
      std::make_pair(std::make_pair(0, 2), NULL), 
      std::make_pair(std::make_pair(1, 3), NULL), 
      std::make_pair(std::make_pair(3, 0), NULL), 
      std::make_pair(std::make_pair(2, 3), NULL), 
      std::make_pair(std::make_pair(2, 4), NULL), 
      std::make_pair(std::make_pair(4, 3), NULL)
    };
    Graph graph(num_vertices, edge_list);

    // ordered in the graph implementation ordered (which
    // is by using push_front for every new directed edge added)
    std::vector<std::vector<size_t>> expected = 
    {{2, 1}, 
     {3}, 
     {4, 3}, 
     {0},
     {3}};
    
    for (size_t i = 0; i < num_vertices; ++i) {
        auto incident_edges = graph.incidentEdges(i);
        size_t iter = 0;
        for (auto edge_util : *incident_edges)
            REQUIRE( edge_util.first == expected[i][iter++] );
    }
}

TEST_CASE("Graph implementation correctly outputs vertex adjacency") {
    // graph with 5 vertices {0, 1, 2, 3, 4}
    size_t num_vertices = 5;
    std::vector<std::pair<std::pair<size_t, size_t>, double>> edge_list =
    { std::make_pair(std::make_pair(0, 1), NULL), 
      std::make_pair(std::make_pair(0, 2), NULL), 
      std::make_pair(std::make_pair(1, 3), NULL), 
      std::make_pair(std::make_pair(3, 0), NULL), 
      std::make_pair(std::make_pair(2, 3), NULL), 
      std::make_pair(std::make_pair(2, 4), NULL), 
      std::make_pair(std::make_pair(4, 3), NULL)
    };
    Graph graph(num_vertices, edge_list);


    std::vector<std::pair<std::pair<size_t, size_t>, double>>& expected = edge_list;
    
    for (auto edge : edge_list) 
        REQUIRE( graph.areAdjacent(edge.first.first, edge.first.second) );
}

TEST_CASE("Graph correctly outputs whether a vertex is source(only outgoing edges) or sink(only incoming edges)") {
    size_t num_vertices = 5;

    // a cyclic linkedlist-like graph structure 
    std::vector<std::pair<std::pair<size_t, size_t>, double>> edge_list =
    { std::make_pair(std::make_pair(0, 1), NULL),    // 0 is source 
      std::make_pair(std::make_pair(1, 2), NULL),    // 1 and 2 are neither source nor sink 
      std::make_pair(std::make_pair(2, 3), NULL),    // 2 and 3 are neither source nor sink
      std::make_pair(std::make_pair(3, 4), NULL)     // 4 is sink 
    };

    Graph graph(num_vertices, edge_list);

    std::vector<bool> source_expected = {true, false, false, false, false};
    std::vector<bool> sink_expected = {false, false, false, false, true};

    for (size_t i = 0; i < num_vertices; ++i) {
        REQUIRE( graph.source(i) == source_expected[i] );
        REQUIRE( graph.sink(i) == sink_expected[i] );
    } 

    //a cyclic graph (which obviously has no source or sink vertices)
    edge_list =
    { std::make_pair(std::make_pair(0, 1), NULL),    
      std::make_pair(std::make_pair(1, 2), NULL),   
      std::make_pair(std::make_pair(2, 3), NULL),    
      std::make_pair(std::make_pair(3, 4), NULL),  
      std::make_pair(std::make_pair(4, 0), NULL)   
    };

    Graph graph1(num_vertices, edge_list);

    for (size_t i = 0; i < num_vertices; ++i) {
        REQUIRE( graph1.source(i) == false );
        REQUIRE( graph1.sink(i) == false );
    } 
}

TEST_CASE ("Graph correctly outputs whether a vertex is edgeless disconnected") {
    size_t num_vertices = 5;
    /* no edges in our graph - all nodes are disconnected */
    std::vector<std::pair<std::pair<size_t, size_t>, double>> edge_list = {};
    Graph graph(num_vertices, edge_list);

    
    // testing vertices correctly loaded in adjancency matrix of edgeless graph 
    REQUIRE ( graph.empty() != true );
    for (size_t i = 0; i < num_vertices; ++i) {
        REQUIRE( graph.exist(i) );
    }
    // no adjacent pairs of vertices exist 
    for (size_t i = 0; i < num_vertices; ++i) {
        auto incident_edges = graph.incidentEdges(i);
        REQUIRE ( incident_edges->size() == 0 );
        for (size_t j = i+1; j < num_vertices; ++j) {
            REQUIRE( graph.areAdjacent(i, j) == false );
            REQUIRE( graph.areAdjacent(j, i) == false ); // reverse direction
        }
    }
}

TEST_CASE ("Graph correctly maps the weights to their corresppoding edge") {
    size_t num_vertices = 5;
    /* no edges in our graph - all nodes are disconnected */
    std::vector<std::pair<std::pair<size_t, size_t>, double>> edge_list = {};
    Graph graph(num_vertices, edge_list);

    
    // testing vertices correctly loaded in adjancency matrix of edgeless graph 
    REQUIRE ( graph.empty() != true );
    for (size_t i = 0; i < num_vertices; ++i) {
        REQUIRE( graph.exist(i) );
    }
    // no adjacent pairs of vertices exist 
    for (size_t i = 0; i < num_vertices; ++i) {
        auto incident_edges = graph.incidentEdges(i);
        REQUIRE ( incident_edges->size() == 0 );
        for (size_t j = i+1; j < num_vertices; ++j) {
            REQUIRE( graph.areAdjacent(i, j) == false );
            REQUIRE( graph.areAdjacent(j, i) == false ); // reverse direction
        }
    }
}






