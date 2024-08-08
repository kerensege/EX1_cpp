
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

int Algorithms::shortestPath(Graph g, int start, int end)
{
    int *dist = new int[g.getNumV()];
    int *pai = new int[g.getNumV()];

    for (int i = 0; i < g.getNumV(); i++)
    {
        dist[i] = INT_MAX / 2; // to avoid overflow
        pai[i] = 0;
    }
    if (g.getWeight(start, start) < 0)
    {
        std::cout << "negative cycle";
        return -1;
    }
    dist[start] = 0;

    for (int i = 0; i < g.getNumV(); i++)
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

void Algorithms::isVisited(Graph g, int v, bool visited[], int previous[], int end *)
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
        previous[neighbList[i]] = v;
        isVisited(g, neighbList[i], visited, previous);
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
    int end * = new int;
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

        if (end != -1)
        {
            int index = end;
            std::cout << end << "<-";
            while (previous[index] != start)
            {
                std::cout << previous[index] << "<-";
                index = previous[index];
            }

            return end;
            
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

