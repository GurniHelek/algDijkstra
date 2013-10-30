#include <iostream>
#include <map>
#include <list>

const int MIN_DENSITY   = 0;
const int MAX_DENSITY   = 100;
const int MIN_DISTANCE  = 1;
const int MAX_DISTANCE  = 100;

typedef struct edge_st
{
    int     vertex;
    int     distance;
    bool    isVisited;
} edge;

typedef std::list<edge> edgeContatiner;
typedef std::map< int, edgeContatiner > graphContainer;

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
    edgeContatiner::iterator getEdges(int x);
    bool isAdjacent(int x, int y);
    bool addEdge(int x, int y, int distance);
    bool addVertex(int x);
    bool deleteEdge(int x, int y);
    void makeRandomGraph(int density, int minDistance, int maxDistance);
    void showGraph();
};

Graph::Graph()
{
    numberOfVertices = 0;
    numberOfEdges    = 0;
}

Graph::Graph(int aNumberOfVertices)
{
    numberOfVertices = aNumberOfVertices;
    numberOfEdges    = 0;

    for (int i = 1; i <= numberOfVertices; i++) {
        edgeContatiner edges;
        graph.insert(std::pair< int, edgeContatiner >(i, edges));
    }
}

int Graph::getNumberOfEdges()
{
    return numberOfEdges;
}

int Graph::getNumberOfVertices()
{
    return numberOfVertices;
}

graphContainer Graph::getGraph()
{
    return graph;
}

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

edgeContatiner::iterator Graph::getEdges(int x)
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
 * @brief Graph::addEdge
 * @param x - first node to be connected
 * @param y - second node to be connected
 * @return true if this node was successfully connetced, false otherwise
 */
bool Graph::addEdge(int x, int y, int distance)
{
    if (x < 1 || y < 1) {
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

//        output = min + (rand() % (int)(max - min + 1))

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


    }
}

int main()
{
/*
    Graph g = Graph(4);


    g.addEdge(1, 2, 13);
    g.addEdge(2, 3, 6);
    g.addEdge(5, 3, 6);
    g.addEdge(1, 4, 6);
    g.addEdge(1, 3, 6);
    std::cout << "Number of v : " << g.getNumberOfVertices() << std::endl;
    std::cout << "Number of e : " << g.getNumberOfEdges() << std::endl;

//    g.makeRandomGraph();

    g.showGraph();

    g.deleteEdge(1, 2);

    std::cout << "Number of v : " << g.getNumberOfVertices() << std::endl;
    std::cout << "Number of e : " << g.getNumberOfEdges() << std::endl;
    g.showGraph();
*/
    Graph rg = Graph();

    rg.makeRandomGraph(10, 1, 5);

    std::cout << "Number of v : " << rg.getNumberOfVertices() << std::endl;
    std::cout << "Number of e : " << rg.getNumberOfEdges() << std::endl;
    rg.showGraph();

    std::cout << "END \n";

    return 0;
}
