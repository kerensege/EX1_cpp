#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
using std::vector;

namespace ariel {

    class Graph {
    private:
        std::vector<std::vector<float>> adjMatrix;
        int numVertices;
        int numEdges;

    public:
        Graph();
        int getNumV();
        void loadGraph(const std::vector<std::vector<int>>& graph);
        void printGraph() const;
        vector<int> getNeighb(int v) const; 
        Graph transpose();
        int getWeight(int source, int dest);

    };

}; 



#endif // GRAPH_HPP
