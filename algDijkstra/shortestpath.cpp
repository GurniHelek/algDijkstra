// *************************************************************************
// ******** Dijkstra algorithm implementation ******************************
// *************************************************************************

#include "shortestpath.h"

/**
 * @brief ShortestPath::ShortestPath - find pathes to all nodes from node start
 * @param g - already initialized graph
 * @param start - start node
 */
ShortestPath::ShortestPath(Graph g, int start)
{
    int n = g.getNumberOfVertices();
    int startIndex = start - 1;
    std::set< std::pair<double, int> > vertexQueue;

    previous.clear();
    minDistance.clear();
    previous.resize(n, -1);
    minDistance.resize(n, INFINITY_VAL);

    minDistance[startIndex] = 0.0;
    vertexQueue.insert(std::make_pair(minDistance[startIndex], startIndex));

    while (!vertexQueue.empty()) {

        double dist = vertexQueue.begin()->first;
        int u       = vertexQueue.begin()->second;
        vertexQueue.erase(vertexQueue.begin());

        edge_t neibourghs = g.getNeighbors(u + 1);
        edge_t::iterator neighborIter = neibourghs.begin();

        for (unsigned int i = 0; i < neibourghs.size(); i++) {

            int v        = neighborIter->vertex - 1;
            double weight = neighborIter->distance;
            double cost   = dist + weight;

            if (cost < minDistance[v]) {
                vertexQueue.erase(std::make_pair(minDistance[v], v));
                minDistance[v] = cost;
                previous[v] = u;
                vertexQueue.insert(std::make_pair(minDistance[v], v));
            }
            neighborIter++;
        }
    }
}

/**
 * @brief ShortestPath::getPath - get shortest path to node end if exist
 * @param end - destination node
 * @param path - finded shortest path
 * @return true if path from start node to end node exist, false otherwise
 */
bool ShortestPath::getPath(int end, path_t &path)
{
    std::list<int> edges;
    bool isPath  = false;
    int endIndex = end - 1;

    if (previous.empty()) {
        return false;
    }

    path.clear();

    for ( ; endIndex != -1; endIndex = previous[endIndex]) {
        edges.push_front(endIndex + 1);
    }

    for (std::list<int>::iterator it = edges.begin();
         it != edges.end();
         it++) {

        path.push_back(*it);
        isPath  = true;
    }

    return isPath;
}

/**
 * @brief ShortestPath::getPathSize - get shortest path length to node end if exist
 * @param end - destination node
 * @return path length if path from start node to end node exist, 0 otherwise
 */
double ShortestPath::getPathSize(int end)
{
    return (minDistance[end - 1] == INFINITY_VAL) ? 0.0 : minDistance[end - 1];
}
