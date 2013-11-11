// *************************************************************************
// ******** Graph implementation *******************************************
// *************************************************************************

#include "graph.h"
#include <sstream>
/**
 * @brief getRandNumber - get random number in range
 * @param min - min number in range
 * @param max - max number in range
 * @return
 */
inline double getRandNumber(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

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

std::vector<std::string>& Graph::split(const std::string &s, char delim, std::vector<std::string> &elems) {
               std::stringstream ss(s);
                std::string item;
                while (std::getline(ss, item, delim)) {
                             elems.push_back(item);
                 }
          return elems;
}

std::vector<std::string> Graph::split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
}

Graph::Graph(const char* filename)
{
    std::string line;
    std::ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        std::cout << "Opening file '" << filename << "' failed! \n";
        return;
    }

    int counter = 0;
    while (std::getline(file, line)) {

        if (!counter) {
            numberOfEdges    = 0;
            numberOfVertices = 0;
        }
        else {
            std::vector<std::string> strEdge = split(line, ' ');

            addEdge(atoi(strEdge[0].c_str()) + 1,
                    atoi(strEdge[1].c_str()) + 1,
                    atoi(strEdge[2].c_str()));
        }
        counter++;
    }

    file.close();
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
 * @return list with neighbors of node x
 */
edge_t Graph::getNeighbors(int x)
{
    edge_t neighbors;

    if (x < 1 || x > numberOfVertices) {
        return neighbors;
    }

    graph_t::iterator node = graph.find(x);
    neighbors = node->second;

    return neighbors;
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
bool Graph::addEdge(int x, int y, double distance)
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
    edge newEdgeY = {y, distance};
    nodeY->second.push_back(newEdgeY);

    graph_t::iterator nodeX = graph.find(y);
    edge newEdgeX = {x, distance};
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
void Graph::makeRandomGraph(double density, double minDistance, double maxDistance)
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
        for (int i = (*iter).first; i <= numberOfVertices; i++) {
            double probability = getRandNumber(MIN_DENSITY, MAX_DENSITY);
            if (probability < density && i != (*iter).first) {
                this->addEdge((*iter).first,
                              i,
                              getRandNumber(minDistance, maxDistance));
            }
        }
    }
}
