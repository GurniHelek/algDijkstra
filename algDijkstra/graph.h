#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <set>
#include <list>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>

const double MIN_DENSITY   = 0.0;
const double MAX_DENSITY   = 1.0;
const double MIN_DISTANCE  = 1.0;
const double MAX_DISTANCE  = 10.0;
const double INFINITY_VAL  = 4242.4242;    // to mark unvisited nodes

typedef struct edge_st
{
    int     vertex;
    double   distance;
} edge;

typedef std::list<edge>         edge_t;
typedef std::map< int, edge_t > graph_t;
typedef std::vector<double>     path_t;


/**
 * @brief The Graph class - implementation of graph
 */
class Graph
{
private:
    int             numberOfVertices;
    int             numberOfEdges;
    graph_t  graph;

public:
    Graph();
    Graph(int numberOfVertices);

    int getNumberOfVertices();
    int getNumberOfEdges();
    graph_t getGraph();
    edge_t getNeighbors(int x);
    bool getEdge(edge& e, int x, int y);
    bool isAdjacent(int x, int y);
    bool addEdge(int x, int y, double distance);
    bool addVertex(int x);
    bool deleteEdge(int x, int y);
    void showGraph();
    void makeRandomGraph(double density, double minDistance, double maxDistance);
};

#endif // GRAPH_H
