/**
 * @file graph.cpp
 * Implementation of an Adjacency List graph structure. 
 *
 * @author Ravi Patel 
 */

#include "graph.h"

#include <iostream> // std::cout, std::endl, std::cerr
#include <queue>    // std::queue
#include <iterator> // std::iterator

// https://github.com/ben-strasser/fast-cpp-csv-parser
# include "fast-cpp-csv-parser-master/csv.h" // C++ based csv parser 


#include "utility_functions.h" // haversine(), float_equal()
#include "min_heap.h"

namespace cs225_fp {
Graph::Graph(const std::string &airport_data_filepath, const std::string &route_data_filepath) 
: Graph(airport_data_filepath, route_data_filepath, -1){
}

Graph::Graph(const std::string &airport_data_filepath, const std::string &route_data_filepath, int size) {
     // read airport data (lat, long) using CSV parser     
    const size_t NUM_COL_IN_AIRPORT_REFINED = 2;
    io::CSVReader<NUM_COL_IN_AIRPORT_REFINED> in1(airport_data_filepath);
    in1.read_header(io::ignore_extra_column, "Latitude", "Longitude");

    double latitude, longitude;

    airport_locating_points_ = {};
    while(in1.read_row(latitude, longitude))
        airport_locating_points_.push_back(std::make_pair(latitude, longitude));
    // num_vertices_ = airport_locating_points_.size();
    num_vertices_ = size > 0 ? size : airport_locating_points_.size();

    // read routes data to construct adjacency list using CSV parser 
    const size_t NUM_COL_IN_ROUTE_REFINED = 2;
    io::CSVReader<NUM_COL_IN_ROUTE_REFINED> in2(route_data_filepath);
    in2.read_header(io::ignore_extra_column, "Source Airport ID", "Destination Airport ID");

    size_t src_airport_id, dest_airport_id;

    // initialize the adjacency list with fixed number of vertices 
    adj_list_ = std::vector<std::list<std::pair<size_t, double>>>(num_vertices_);

    // initialize with 0 number of incoming edges for vertices 
    incoming_edges_count_ = std::vector<std::size_t>(num_vertices_, 0);

    while(in2.read_row(src_airport_id, dest_airport_id)) {
        // if (src_airport_id != 0 && dest_airport_id != 0) {
        if (src_airport_id < num_vertices_ && dest_airport_id < num_vertices_) {
            double src_airport_lat   = airport_locating_points_[src_airport_id].first;
            double src_airport_long  = airport_locating_points_[src_airport_id].second;
            double dest_airport_lat  = airport_locating_points_[dest_airport_id].first;
            double dest_airport_long = airport_locating_points_[dest_airport_id].second;

            // distance calcualted using Haversine Formula for a directed edge from source to destination airport
            double haversine_dist = haversine(src_airport_lat, src_airport_long, dest_airport_lat, dest_airport_long);
            adj_list_[src_airport_id].push_front(std::make_pair(dest_airport_id, haversine_dist));

            // update incoming edge count for destination vertex 
            ++incoming_edges_count_[dest_airport_id];
        }   
    }
}

Graph::Graph(
size_t num_vertices, 
const std::vector<std::pair<std::pair<size_t, size_t>, double>>& directed_edge_list) 
: num_vertices_(num_vertices) {
    adj_list_ = std::vector<std::list<std::pair<size_t, double>>>(num_vertices_);
    incoming_edges_count_ = std::vector<size_t>(num_vertices_, 0);
    for (size_t i = 0; i < directed_edge_list.size(); ++i) {
        size_t src = directed_edge_list[i].first.first;
        size_t dest = directed_edge_list[i].first.second;
        adj_list_[src].push_front(std::make_pair(dest, directed_edge_list[i].second));
        ++incoming_edges_count_[dest];
    }
    airport_locating_points_= {};
}


const std::list<std::pair<size_t, double>>* Graph::incidentEdges(size_t v) const {
    return &adj_list_[v];
}

bool Graph::areAdjacent(size_t src, size_t dest) {
    if (src >= adj_list_.size() || dest >= adj_list_.size()) 
        std::cerr << "Error: The source and/or destination vertex provided does not exist.";
    std::list<std::pair<size_t, double>>& incident_edges = adj_list_[src];
    for (const std::pair<size_t, double>& edge_util : incident_edges) {
        if (edge_util.first == dest) {
            return true;
        }
    }
    return false;
}

void Graph::printAirportDetails(void) {
    for (size_t i = 0; i < 100; ++i) {
        std::cout << i << " {";
        for (std::list<std::pair<size_t, double>>::iterator it=adj_list_[i].begin(); it != adj_list_[i].end(); ++it)
            std::cout << "(" << (*it).first <<  ", " << (*it).second << ") ";
        std::cout << "}" << std::endl;
    }
    // for (size_t i = 0; i < airport_locating_points_.size(); ++i) 
    //     std::cout << i << ", " << airport_locating_points_[i].first << ", " << airport_locating_points_[i].second << std::endl; 
}

std::vector<size_t>* Graph::BFS(size_t starting_vertex) const {
    if (this->empty()) 
        return NULL;

    std::vector<size_t>* vertex_traversal_list = new std::vector<size_t>();
    vertex_traversal_list->reserve(num_vertices_);
    
    std::vector<bool> visited(num_vertices_, false);  
    
    // this BFSUtil() function call would traverse over all vertices if our graph is one connected component
    BFSUtil(starting_vertex, visited, vertex_traversal_list);

    // for traversing over the disconnected components (in ascending order of the vertex)
    for (size_t curr_vertex = 0; curr_vertex < num_vertices_; curr_vertex++) {
        if (visited[curr_vertex] == false) {
            BFSUtil(curr_vertex, visited, vertex_traversal_list); 
        }
    }

    return vertex_traversal_list;
}

void Graph::BFSUtil(size_t curr_vertex, std::vector<bool> &visited, std::vector<size_t>* vertex_traversal_list) const {
    std::queue<size_t> queue;
    
    visited[curr_vertex] = true;
    queue.push(curr_vertex);
    
    while(!queue.empty()) {
        curr_vertex = queue.front();
        vertex_traversal_list->push_back(curr_vertex);
        queue.pop();

        // get all the adjacent vertices of the last dequeued vertex 
        std::list<std::pair<size_t, double>>::iterator edge_iter;

        for (const std::pair<size_t, double> &edge_container : adj_list_[curr_vertex]) {
            if (!visited[edge_container.first]) {
                visited[edge_container.first] = true;
                queue.push(edge_container.first);
            }
        }
    }  
}

// important public utility functions 
bool Graph::empty(void) const { 
    return num_vertices_ == 0; 
}

size_t Graph::size() const { 
    return num_vertices_; 
}

bool Graph::exist(size_t v) const { 
    return v < num_vertices_; 
}

size_t Graph::getIncomingEdgeCount(size_t v) const { 
    return incoming_edges_count_[v]; 
}

size_t Graph::getOutgoingEdgeCount(size_t v) const { 
    return adj_list_[v].size(); 
}

bool Graph::source(size_t v) const {
    return getIncomingEdgeCount(v) == 0 && getOutgoingEdgeCount(v) > 0;
}

bool Graph::sink(size_t v) const {
    return getIncomingEdgeCount(v) > 0 && getOutgoingEdgeCount(v) == 0;
}

bool Graph::disconnected(size_t v) const { 
    return !(getIncomingEdgeCount(v) || getOutgoingEdgeCount(v)); 
}
}

