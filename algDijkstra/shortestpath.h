#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "graph.h"

/**
 * @brief The ShortestPath class - implementation of Dijkstra algorithm
 */
class ShortestPath
{
private:
    path_t  shortestPath;
    path_t  minDistance;
    path_t  previous;

public:
    ShortestPath();
    ShortestPath(Graph g, int start);

    double getPathSize(int end);
    bool  getPath(int end, path_t &path);

};

#endif // SHORTESTPATH_H
