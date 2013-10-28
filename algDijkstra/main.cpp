#include <iostream>
#include <set>
#include <map>

typedef struct edge_st
{
    int     vertex;
    int     distance;
    bool    isVisited;
} edge;

typedef std::map< int, std::set<edge> > graphContainer;

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
    bool isAdjacent(int x, int y);
    bool addEdge(int x, int y);
    void makeRandomGraph(int density, int minDistance, int maxDistance);
};

Graph::Graph()
{
    numberOfVertices = 0;
    numberOfEdges    = 0;
}

Graph::Graph(int aNumberOfVertices)
{
    numberOfVertices = aNumberOfVertices;

    for (int i = 1; i <= numberOfVertices; i++) {
        std::set<edge> edges;
        graph.insert(std::pair< int, std::set<edge> >(i, edges));
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
    if (x < 0 || x > numberOfVertices &&
        y < 0 || y > numberOfVertices) {
        return false;
    }
    graphContainer::iterator node = graph.find(x);

}

/**
 * @brief Graph::addEdge
 * @param x - first node to be connected
 * @param y - second node to be connected
 * @return true if this node was successfully connetced, false otherwise
 */
bool Graph::addEdge(int x, int y)
{
    if (x < 0 || x > numberOfVertices &&
        y < 0 || y > numberOfVertices) {
        return false;
    }
    graphContainer::iterator node = graph.find(x);

}

void Graph::makeRandomGraph(int density, int minDistance, int maxDistance)
{
    for (graphContainer::iterator iter = graph.begin(); iter != graph.end(); ++iter) {

    }
}

int main()
{


    return 0;
}
