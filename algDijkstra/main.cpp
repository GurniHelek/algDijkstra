#include <iostream>
#include <map>
#include <set>
#include <list>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>
#include <climits>

const int MIN_DENSITY   = 0;
const int MAX_DENSITY   = 100;
const int MIN_DISTANCE  = 1;
const int MAX_DISTANCE  = 10;

typedef struct edge_st
{
    int     vertex;
    int     distance;
    bool    isVisited;
} edge;

typedef std::list<edge>         edge_t;
typedef std::map< int, edge_t > graph_t;
typedef std::vector<int>        path_t;

/**
 * @brief getRandNumber - get random integer in range
 * @param min - min number in range
 * @param max - max number in range
 * @return
 */
inline int getRandNumber(int min, int max)
{
    return min + (rand() % (int)(max - min + 1));
}

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
    bool addEdge(int x, int y, int distance);
    bool addVertex(int x);
    bool deleteEdge(int x, int y);
    void showGraph();
    void makeRandomGraph(int density, int minDistance, int maxDistance);
};

/**
 * @brief Graph::Graph - default constructor that creates empty graph
 */
Graph::Graph()
{
    numberOfVertices = 0;
    numberOfEdges    = 0;
}

/**
 * @brief Graph::Graph - constructor that creates graph with N unconnected vertices
 * @param N - number of vertices in graph
 */
Graph::Graph(int N)
{
    numberOfVertices = N;
    numberOfEdges    = 0;

    for (int i = 1; i <= numberOfVertices; i++) {
        edge_t edges;
        graph.insert(std::pair< int, edge_t >(i, edges));
    }
}

/**
 * @brief Graph::getNumberOfEdges
 * @return number of edges in graph
 */
int Graph::getNumberOfEdges()
{
    return numberOfEdges;
}

/**
 * @brief Graph::getNumberOfVertices
 * @return number of vertices in graph
 */
int Graph::getNumberOfVertices()
{
    return numberOfVertices;
}

/**
 * @brief Graph::getGraph
 * @return current graph
 */
graph_t Graph::getGraph()
{
    return graph;
}

/**
 * @brief Graph::getNeighbors - get list with neighbors of node x
 * @param x - node x
 * @return
 */
edge_t Graph::getNeighbors(int x)
{
    edge_t neighbors;

    if (x < 1 || x > numberOfVertices) {
        return neighbors;
    }

    graph_t::iterator node = graph.find(x);

//    neighbors = node->second;

    return node->second;;
}

/**
 * @brief Graph::getEdge - get edge between nodes x and y if exist
 * @param e - edge container
 * @param x - node x
 * @param y - node y
 * @return true if edge exist, otherwise false
 */
bool Graph::getEdge(edge& e, int x, int y)
{
    if (!isAdjacent(x, y)) {
        return false;
    }

    graph_t::iterator node = graph.find(x);

    for (edge_t::iterator edges = node->second.begin();
         edges != node->second.end();
         edges++) {
        if ((*edges).vertex == y) {
            e = *edges;
            return true;
        }
    }
    return true;
}

/**
 * @brief Graph::isAdjacent - tests whether there is an edge from node x to node y
 * @param x - node x
 * @param y - node y
 * @return true if there is an edge from node x to node y, otherwise false
 */
bool Graph::isAdjacent(int x, int y)
{
    if ((x < 1 || x > numberOfVertices) ||
        (y < 1 || y > numberOfVertices)) {
        return false;
    }
    graph_t::iterator node = graph.find(x);

    for (edge_t::iterator edges = node->second.begin();
         edges != node->second.end();
         edges++) {
        if ((*edges).vertex == y) {
            return true;
        }
    }

    return false;
}

/**
 * @brief Graph::addVertex - adds node to graph if it is not there
 * @param x - node x
 * @return true if new node was added, otherwise false
 */
bool Graph::addVertex(int x)
{
    if (x <= numberOfVertices) {
        return false;
    }

    edge_t edges;
    graph.insert(std::pair< int, edge_t >(x, edges));
    numberOfVertices++;

    return true;
}

/**
 * @brief Graph::addEdge - adds to graph the edge from x to y, if it is not there.
 * @param x - first node to be connected
 * @param y - second node to be connected
 * @param distance - distance between nodes
 * @return true if this node was successfully connetced, otherwise false
 */
bool Graph::addEdge(int x, int y, int distance)
{
    if ((x < 1 || y < 1) || (x == y)) {
        return false;
    }

    if (x > numberOfVertices) {
        for (int i = numberOfVertices; i <= x; ++i) {
            addVertex(i);
        }
    }

    if (y > numberOfVertices) {
        for (int i = numberOfVertices; i <= y; ++i) {
            addVertex(i);
        }
    }

    if (isAdjacent(x, y)) {
        return true;
    }

    graph_t::iterator nodeY = graph.find(x);
    edge newEdgeY = {y, distance, false};
    nodeY->second.push_back(newEdgeY);

    graph_t::iterator nodeX = graph.find(y);
    edge newEdgeX = {x, distance, false};
    nodeX->second.push_back(newEdgeX);

    numberOfEdges++;

    return true;
}

/**
 * @brief Graph::deleteEdge - removes the edge from x to y, if it is there.
 * @param x - node x
 * @param y - node y
 * @return true if edge was successfully removed, otherwise false
 */
bool Graph::deleteEdge(int x, int y)
{
    if ((x < 1 || x > numberOfVertices) ||
        (y < 1 || y > numberOfVertices)) {
        return false;
    }

    if (!isAdjacent(x, y)) {
        return true;
    }

    graph_t::iterator nodeX = graph.find(x);
    for (edge_t::iterator edgesX = nodeX->second.begin();
         edgesX != nodeX->second.end();
         edgesX++) {
        if ((*edgesX).vertex == y) {
            nodeX->second.erase(edgesX);
            break;
        }
    }

    graph_t::iterator nodeY = graph.find(y);
    for (edge_t::iterator edgesY = nodeY->second.begin();
         edgesY != nodeY->second.end();
         edgesY++) {
        if ((*edgesY).vertex == x) {
            nodeY->second.erase(edgesY);
            break;
        }
    }

    numberOfEdges--;

    return true;
}
/**
 * @brief Graph::showGraph - print graph
 */
void Graph::showGraph()
{
    for (graph_t::iterator iter = graph.begin(); iter != graph.end(); ++iter) {
        std::cout << (*iter).first;
        for (edge_t::iterator edges = iter->second.begin();
             edges != iter->second.end();
             edges++) {
            std::cout << " -> " << (*edges).vertex << " (" << (*edges).distance << ")";
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Graph::makeRandomGraph - randomly add edges with random distance in graph
 * @param density - edge density
 * @param minDistance - min allowed distance
 * @param maxDistance - max allowed distance
 */
void Graph::makeRandomGraph(int density, int minDistance, int maxDistance)
{
    if (density > MAX_DENSITY || density < MIN_DENSITY) {
        density = MAX_DENSITY;
    }

    if (minDistance > maxDistance) {
        int tmpDist = maxDistance;
        maxDistance = minDistance;
        minDistance = tmpDist;
    }

    if (minDistance > MAX_DISTANCE || minDistance < MIN_DISTANCE) {
        minDistance = MAX_DISTANCE;
    }

    if (maxDistance > MAX_DISTANCE || maxDistance < MIN_DISTANCE) {
        maxDistance = MAX_DISTANCE;
    }

    for (graph_t::iterator iter = graph.begin(); iter != graph.end(); ++iter) {
        int probability = getRandNumber(MIN_DENSITY, MAX_DENSITY);
        for (int i = (*iter).first; i <= numberOfVertices; i++) {
            if (probability < density) {
                this->addEdge((*iter).first,
                              i,
                              getRandNumber(minDistance, maxDistance));
            }
        }
    }
}

class ShortestPath
{
private:
    path_t  shortestPath;
    path_t  minDistance;
    path_t  previous;

public:
    ShortestPath();
    ShortestPath(Graph g, int start);

    int getPathSize(int end);
    bool getPath(int end, path_t &path);

};

ShortestPath::ShortestPath(Graph g, int start)
{
    int n = g.getNumberOfVertices();
    int startIndex = start - 1;
    std::set< std::pair<int, int> > vertexQueue;

    previous.clear();
    minDistance.clear();
    previous.resize(n, -1);
    minDistance.resize(n, INT_MAX);

    minDistance[startIndex] = 0;
    vertexQueue.insert(std::make_pair(minDistance[startIndex], startIndex));

    while (!vertexQueue.empty()) {

        int dist = vertexQueue.begin()->first;
        int u    = vertexQueue.begin()->second;
        vertexQueue.erase(vertexQueue.begin());

        edge_t neibourghs = g.getNeighbors(u + 1);
        edge_t::iterator neighborIter = neibourghs.begin();

        for (int i = 0; i < neibourghs.size(); i++) {

            int v      = neighborIter->vertex - 1;
            int weight = neighborIter->distance;
            int cost   = dist + weight;

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

bool ShortestPath::getPath(int end, path_t &path)
{
    std::list<int> edges;
    bool isPath  = false;
    int endIndex = end - 1;

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

int ShortestPath::getPathSize(int end)
{
    return (minDistance[end - 1] == INT_MAX) ? 0 : minDistance[end - 1];
}

int main()
{
    srand (time(NULL));



    Graph rg = Graph(50);

    rg.makeRandomGraph(40, 1, 10);

    std::cout << "Number of v : " << rg.getNumberOfVertices() << std::endl;
    std::cout << "Number of e : " << rg.getNumberOfEdges() << std::endl;
    rg.showGraph();

/*
    Graph rg = Graph(5);

    rg.addEdge(1, 2, 4);
    rg.addEdge(1, 3, 5);
    rg.addEdge(1, 4, 10);
    rg.addEdge(5, 2, 4);
    rg.addEdge(5, 3, 5);
*/


    ShortestPath p = ShortestPath(rg, 1);
    path_t path;
    int end = 41;

    p.getPath(end, path);
    std::cout << "Path : [" << p.getPathSize(end) << "] ";
    for (path_t::iterator it = path.begin(); it != path.end(); it++)
    {
        std::cout << *it << " -> " ;
    }
    std::cout << std::endl;

    std::cout << "END \n";

    return 0;
}
