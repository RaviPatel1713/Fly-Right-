#include "../cs225/catch/catch.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// add required header files to be tested 
#include "../graph.h"

using cs225_fp::Graph;

/**
 * This test suite is designed specifically for testing the BFS graph traversal 
 * implemented for adjacency list graph structure  
 */

void assert_equal_vectors(const std::vector<size_t>& a, const std::vector<size_t>& b) {
  REQUIRE( a.size() == b.size() );
  for (size_t i = 0; i < a.size(); ++i) 
    REQUIRE ( a[i] == b[i] );
}

TEST_CASE ("BFS traversal empty traversal list with for empty graph") {
    size_t num_vertices = 0;
    std::vector<std::pair<std::pair<size_t, size_t>, double>> edge_list = {};
    Graph graph(0, edge_list);
    REQUIRE( graph.BFS(0) == NULL );
}

TEST_CASE("BFS traversal starts at the correct starting point with connected graph") {
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

    for (size_t i = 0; i < num_vertices; ++i) {
      REQUIRE( graph.BFS(i)->front() == i );
    }
}

TEST_CASE("BFS traversal visits the nodes in correct order for connected graph") {
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

    std::vector<std::vector<size_t>> expected_bfss;
    expected_bfss = 
    {{0, 2, 1, 4, 3},   // bfs starting at 0
     {1, 3, 0, 2, 4},   // bfs starting at 1
     {2, 4, 3, 0, 1},   // bfs starting at 2
     {3, 0, 2, 1, 4},   // bfs starting at 3
     {4, 3, 0, 2, 1}};  // bfs starting at 4
    for (size_t i = 0; i < num_vertices; ++i) 
      assert_equal_vectors(*graph.BFS(i), expected_bfss[i]);
}

TEST_CASE("BFS traversal visits the nodes in correct order for a graph with multiple connected components") {
  size_t num_vertices = 6;
    std::vector<std::pair<std::pair<size_t, size_t>, double>> edge_list =
    { std::make_pair(std::make_pair(0, 1), NULL), 
      std::make_pair(std::make_pair(0, 2), NULL), 
      std::make_pair(std::make_pair(1, 3), NULL), 
      std::make_pair(std::make_pair(3, 0), NULL), 
      std::make_pair(std::make_pair(2, 3), NULL), 
      std::make_pair(std::make_pair(2, 4), NULL), 
      std::make_pair(std::make_pair(4, 3), NULL) };
    Graph graph(num_vertices, edge_list);

    std::vector<std::vector<size_t>> expected_bfss;
    expected_bfss = 
    {{0, 2, 1, 4, 3, 5},   // bfs starting at 0
     {1, 3, 0, 2, 4, 5},   // bfs starting at 1
     {2, 4, 3, 0, 1, 5},   // bfs starting at 2
     {3, 0, 2, 1, 4, 5},   // bfs starting at 3
     {4, 3, 0, 2, 1, 5}, 
     {5, 0, 2, 1, 4, 3}};  // bfs starting at 4
    for (size_t i = 0; i < num_vertices; ++i) 
      assert_equal_vectors(*graph.BFS(i), expected_bfss[i]);
}

TEST_CASE("BFS traversal visits the nodes in correct order for an edgeless graph (graph with each vertex as connected component)") {
  size_t num_vertices = 6;
    std::vector<std::pair<std::pair<size_t, size_t>, double>> edge_list = {};
    Graph graph(num_vertices, edge_list);

    std::vector<std::vector<size_t>> expected_bfss;
    expected_bfss = 
    {{0, 1, 2, 3, 4, 5},   // bfs starting at 0
     {1, 0, 2, 3, 4, 5},   // bfs starting at 1
     {2, 0, 1, 3, 4, 5},   // bfs starting at 2
     {3, 0, 1, 2, 4, 5},   // bfs starting at 3
     {4, 0, 1, 2, 3, 5}, 
     {5, 0, 1, 2, 3, 4}};  // bfs starting at 4
    for (size_t i = 0; i < num_vertices; ++i) 
      assert_equal_vectors(*graph.BFS(i), expected_bfss[i]);
}

TEST_CASE("BFS traversal visits the nodes in correct order for a strongly connected graph") {
    size_t num_vertices = 5;
    std::vector<std::pair<std::pair<size_t, size_t>, double>> edge_list;
    edge_list.reserve(num_vertices * (num_vertices - 1));
    for (size_t u = 0; u < num_vertices; ++u) {
      for (size_t v = u+1; v < num_vertices; ++v) {
        edge_list.push_back(std::make_pair(std::make_pair(u, v), NULL));
        edge_list.push_back(std::make_pair(std::make_pair(v, u), NULL));
      }
    }

    Graph graph(num_vertices, edge_list);

    std::vector<std::vector<size_t>> expected_bfss;
    expected_bfss = 
    {{0, 4, 3, 2, 1},   // bfs starting at 0
     {1, 4, 3, 2, 0},   // bfs starting at 1
     {2, 4, 3, 1, 0},   // bfs starting at 2
     {3, 4, 2, 1, 0},   // bfs starting at 3
     {4, 3, 2, 1, 0}};  // bfs starting at 4
    for (size_t i = 0; i < num_vertices; ++i) 
      assert_equal_vectors(*graph.BFS(i), expected_bfss[i]);
}









