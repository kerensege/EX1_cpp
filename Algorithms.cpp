
#include "Algorithms.hpp"
#include <limits.h>

void Algorithms::DFS(Graph g, int v, bool visited[])
{
    vector<int> neighbList;
    if (visited[v] == true)
    {
        return;
    }
    visited[v] = true;
    neighbList = g.getNeighb(v);
    for (int i = 0; i < neighbList.size(); i++)
    {
        DFS(g, neighbList[i], visited);
    }
}

int Algorithms::isConnected(Graph g)
{
    bool *visited = new bool[g.getNumV()];
    for (int i = 0; i < g.getNumV(); i++)
    {
        visited[i] = false;
    }

    DFS(g, 0, visited);
    for (int i = 0; i < g.getNumV(); i++)
    {
        if (visited[i] == false)
        {
            return 0;
        }
    }

    Graph gT = g.transpose();
    for (int i = 0; i < g.getNumV(); i++)
    {
        visited[i] = false;
    }
    DFS(gT, 0, visited);
    for (int i = 0; i < g.getNumV(); i++)
    {
        if (visited[i] == false)
        {
            return 0;
        }
    }
    return 1;
}

int Algorithms::shortestPath(Graph g, int start, int end) // belman-ford algorithm
{
    int *dist = new int[g.getNumV()];
    int *pai = new int[g.getNumV()];

    negativeFinder(g,dist,pai,start);
    // if (g.getWeight(start, start) < 0)  //to avoid getting stuck in first negative cycle
    // {
    //     std::cout << "negative cycle";
    //     return -1;
    // }
   

    if (dist[end] < INT_MAX / 2)
    {
        int index = end;
        std::cout << end << "<-";
        while (pai[index] != start)
        {
            std::cout << pai[index] << "<-";
            index = pai[index];
        }

        return pai[start];
        // return dist[end];
    }
    return -1;
}

void Algorithms::isVisited(Graph g, int v, bool visited[], int previous[], int *end)
{
    vector<int> neighbList;

    if (visited[v] == true)
    {
        *end = v;
        return;
    }
    visited[v] = true;
    neighbList = g.getNeighb(v);

    for (int i = 0; i < neighbList.size(); i++)
    {
        if (previous[v] != neighbList[i])
        {
            previous[neighbList[i]] = v;
            isVisited(g, neighbList[i], visited, previous, end);
        }
    }
}

int Algorithms::isContainsCycle(Graph g)
{
    bool *visited = new bool[g.getNumV()];
    bool *visitedPath = new bool[g.getNumV()];
    for (int i = 0; i < g.getNumV(); i++)
    {
        visited[i] = false;
        visitedPath[i] = false;
    }

    int *previous = new int[g.getNumV()];
    int *end = new int;
    *end = -1;

    for (int i = 0; i < g.getNumV(); i++)
    {
        if (visitedPath[i] != true)
        {
            for (int i = 0; i < g.getNumV(); i++)
            {
                visited[i] = false;
            }

            isVisited(g, i, visited, previous, end);
        }

        if (*end != -1)
        {
            int index = *end;
            std::cout << *end << "<-";
            while (previous[index] != *end)
            {
                std::cout << previous[index] << "<-";
                index = previous[index];
            }
            //  std::cout << "<-"<< *end ;

            return *end;
        }
        for (int i = 0; i < g.getNumV(); i++)
        {
            if (visited[i] == true)
            {
                visitedPath[i] = true;
            }
        }
    }
    return 0;
}

int Algorithms::negativeFinder(Graph g, int *dist, int *pai, int start) // belman-ford algorithm
{

    for (int i = 0; i < g.getNumV(); i++)
    {
        dist[i] = INT_MAX / 2; // to avoid overflow
        pai[i] = 0;
    }

    dist[start] = 0;                      // array that calculate the minimum distance between each vertex and start(first vertex)
    for (int k = 0; k < g.getNumV(); k++) // to make sure we dont have negative cycle
    {

        for (int i = 0; i < g.getNumV(); i++) // run total e times how to improve the path
        {
            std::vector<int> neighbList = g.getNeighb(i);
            for (const auto &v : neighbList)
            {
                if (dist[i] + g.getWeight(i, v) < dist[v])
                {
                    dist[v] = dist[i] + g.getWeight(i, v);
                    pai[v] = i;
                }
            }
        }
    }

    for (int i = 0; i < g.getNumV(); i++) // run one last time to check if it still changes.if it is- we have negative cycle
    {
        std::vector<int> neighbList = g.getNeighb(i);
        for (const auto &v : neighbList)
        {
            if (dist[i] + g.getWeight(i, v) < dist[v])
            {
                std::cout << "negative cycle";
                return -1;
            }
        }
    }
    return 1;
}

void Algorithms::negativeCycle(Graph g)
{
    int finalCheck = 0;
    int *dist = new int[g.getNumV()];
    int *pai = new int[g.getNumV()];
    for (int i = 0; i < g.getNumV(); i++)
    {
        dist[i] = INT_MAX / 2; // to avoid overflow
        pai[i] = 0;
    }

    for (int j = 0; j < g.getNumV(); j++)
    {
        finalCheck = negativeFinder(g, dist, pai, j);
        if (finalCheck == -1)
        {
            std::cout << "negative cycle";
            return;
        }
    }
    std::cout << "does not cointain negative cycle";
}
