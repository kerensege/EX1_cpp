#include "Graph.hpp"
using namespace ariel;

class Algorithms{
    public:
        static int isConnected(Graph g);
        static int shortestPath(Graph g,int start,int end);
        static int isContainsCycle(Graph g);
        static Graph isBipartite(Graph g);
        static void negativeCycle(Graph g);
        static void isVisited(Graph g,int v,bool visited[],int previous[], int* end);
        static int negativeFinder(Graph g, int* dist, int* pai, int start);
    
    private:
        static void DFS(Graph g,int v,bool visited[]);
        

        

};
