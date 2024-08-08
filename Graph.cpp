

#include "Graph.hpp"

namespace ariel {
    int Graph::getNumV(){
        return numVertices;
    }

    Graph::Graph() : numVertices(0), numEdges(0) {}

    void Graph::loadGraph(const std::vector<std::vector<int>>& graph) {
        // Validate the graph matrix
        unsigned long n = graph.size();
        for (const auto& row : graph) {
            if (row.size() != n) {
                throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
        }


        // Allocate and initialize the adjacency matrix
        adjMatrix = std::vector<std::vector<float>>(n, std::vector<float>(n));
        for (unsigned long i = 0; i < n; ++i) {
            for (unsigned long j = 0; j < n; ++j) {
                adjMatrix[i][j] = static_cast<float>(graph[i][j]);
            }
        }
        // adjMatrix = graph;
        numVertices = n;
        numEdges = 0;
        for (unsigned long i = 0; i < n; ++i) {
            for (unsigned long j = i + 1; j < n; ++j) {
                if (adjMatrix[i][j] != 0) {
                    ++numEdges;
                }
            }
        }
    }

    void Graph::printGraph() const {
        std::cout << "Graph with " << numVertices << " vertices and " << numEdges << " edges." << std::endl;
    }


    vector<int> Graph::getNeighb(int v) const{
        vector<int> neighbList;
        for (unsigned long i = 0; i < numVertices; i++){
            if (adjMatrix[static_cast<unsigned long>(v)][i] != 0){
                neighbList.push_back(i);
            }
        }
        return neighbList;
    } 


    Graph Graph::transpose(){
    vector<std::vector<int>> tempG;
    tempG= std::vector<std::vector<int>>(static_cast<unsigned long>(numVertices), std::vector<int>(static_cast<unsigned long>(numVertices)));
        for (unsigned long i = 0; i < numVertices; ++i) {
            for (unsigned long j = 0; j < numVertices; ++j) {
                tempG[i][j] = static_cast<float>(adjMatrix[j][i]);
            }
        }
    Graph g;
    g.loadGraph(tempG);
    return g;

}
    
    int Graph::getWeight(int source, int dest){
       return adjMatrix[source][dest];
    }
    
    
    
    } 
