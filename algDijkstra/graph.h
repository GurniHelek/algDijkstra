#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
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
const double MAX_DISTANCE  = 100.0;
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
    int     numberOfVertices;
    int     numberOfEdges;
    graph_t graph;

    // taken from here : http://stackoverflow.com/a/236803
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);

public:
    Graph();
    Graph(int numberOfVertices);
    Graph(const char* filename);

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
