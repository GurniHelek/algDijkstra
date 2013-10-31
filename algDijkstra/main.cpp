#include <iostream>
#include <map>
#include <list>
#include <cstdlib>
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

typedef std::list<edge> edgeContatiner;
typedef std::map< int, edgeContatiner > graphContainer;

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
    graphContainer  graph;

public:
    Graph();
    Graph(int numberOfVertices);

    int getNumberOfVertices();
    int getNumberOfEdges();
    graphContainer getGraph();
    edgeContatiner::iterator getNeighbors(int x);
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
        edgeContatiner edges;
        graph.insert(std::pair< int, edgeContatiner >(i, edges));
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
graphContainer Graph::getGraph()
{
    return graph;
}

/**
 * @brief Graph::getNeighbors - get list with neighbors of node x
 * @param x - node x
 * @return
 */
edgeContatiner::iterator Graph::getNeighbors(int x)
{
    edgeContatiner::iterator neighbors;

    if (x < 1 || x > numberOfVertices) {
        return neighbors;
    }

    graphContainer::iterator node = graph.find(x);

    neighbors = node->second.begin();

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

    graphContainer::iterator node = graph.find(x);

    for (edgeContatiner::iterator edges = node->second.begin();
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
    graphContainer::iterator node = graph.find(x);

    for (edgeContatiner::iterator edges = node->second.begin();
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

    edgeContatiner edges;
    graph.insert(std::pair< int, edgeContatiner >(x, edges));
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

    graphContainer::iterator nodeY = graph.find(x);
    edge newEdgeY = {y, distance, false};
    nodeY->second.push_back(newEdgeY);

    graphContainer::iterator nodeX = graph.find(y);
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

    graphContainer::iterator nodeX = graph.find(x);
    for (edgeContatiner::iterator edgesX = nodeX->second.begin();
         edgesX != nodeX->second.end();
         edgesX++) {
        if ((*edgesX).vertex == y) {
            nodeX->second.erase(edgesX);
            break;
        }
    }

    graphContainer::iterator nodeY = graph.find(y);
    for (edgeContatiner::iterator edgesY = nodeY->second.begin();
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
    for (graphContainer::iterator iter = graph.begin(); iter != graph.end(); ++iter) {
        std::cout << (*iter).first;
        for (edgeContatiner::iterator edges = iter->second.begin();
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

    for (graphContainer::iterator iter = graph.begin(); iter != graph.end(); ++iter) {
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

void shortPath(Graph g, int start, int end)
{
    int num = g.getNumberOfVertices()+1;
    int i, u, index, count;
    std::vector<int>  distances(num, INT_MAX);
    std::vector<bool> visited(num, false);

    distances[start] = 0;

    for (count=0; count<num-1; count++)
    {
        int min = INT_MAX;
        for (i=0; i < num; i++)
        if (!visited[i] && distances[i] <= min)
        {
            min = distances[i];
            index = i;
        }
        u = index;
        visited[u] = true;
        for (i=0; i < num; i++) {

        edge e;
        g.getEdge(e, u, i);

        if (!visited[i] && g.isAdjacent(u, i) &&
            distances[u] != INT_MAX &&
            distances[u] + e.distance < distances[i] )
            distances[i]=distances[u] + e.distance;
        }
    }

    std::cout<<"Стоимость пути из начальной вершины до остальных:\t\n";
    int m = start;
    for (i=0; i<num; i++) if (distances[i]!=INT_MAX)
    std::cout<<m<<" > "<<i+1<<" = "<<distances[i]<<std::endl;
    else std::cout<<m<<" > "<<i+1<<" = "<<"маршрут недоступен"<<std::endl;
}


int main()
{
    srand (time(NULL));


    /*
    Graph rg = Graph(50);

    rg.makeRandomGraph(40, 1, 10);

    std::cout << "Number of v : " << rg.getNumberOfVertices() << std::endl;
    std::cout << "Number of e : " << rg.getNumberOfEdges() << std::endl;
    rg.showGraph();
*/

    Graph rg = Graph(5);

    rg.addEdge(1, 2, 4);
    rg.addEdge(4, 2, 5);

    edge e;
    if (rg.getEdge(e, 2, 1)) {
        std::cout << "\n\n e : " << e.distance << std::endl;
    }

    std::cout << "END \n";


    shortPath(rg, 1, 5);

    return 0;
}
