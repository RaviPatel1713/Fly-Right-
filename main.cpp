#include <iostream>
#include <set>
#include <vector>

using namespace std;

#include "graph.h"
#include "dijkstra.h"
#include "betweenness_centrality.h"

using cs225_fp::Graph;
using cs225_fp::Dijkstra;
using cs225_fp::BetweennessCentrality;

const string DEFAULT_AIRPORT_DATA_FILEPATH = "dataset/airports_refined.csv";
const string DEFAULT_ROUTE_DATA_FILEPATH = "dataset/routes_refined.csv";

int main(int argc, const char** argv) {
    string airports_file = DEFAULT_ROUTE_DATA_FILEPATH;
    string routes_file = DEFAULT_ROUTE_DATA_FILEPATH;
    int sample_size = 250;

    if (argc == 2) {  
        airports_file = argv[1];
        routes_file = argv[2];
    }
    else if (argc == 3) {
        airports_file = argv[1];
        routes_file = argv[2];
        sample_size = std::stoi(argv[3]);
    }
    
    Graph graph(DEFAULT_AIRPORT_DATA_FILEPATH, DEFAULT_ROUTE_DATA_FILEPATH, sample_size);
    graph.printAirportDetails();
    Dijkstra dijkstra_util(graph);

    BetweennessCentrality btw_centrality_util(graph);
    btw_centrality_util.constructBetweennessCentrality();
    
    std::cout << btw_centrality_util.getHighestImportanceVertex() << std::endl;

    return 0;
}
