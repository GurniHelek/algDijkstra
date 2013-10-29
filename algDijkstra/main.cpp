#include <iostream>
#include <map>
#include <list>

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
    bool isAdjacent(int x, int y);
    bool addEdge(int x, int y, int distance);
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
    if ((x < 1 || x > numberOfVertices) &&
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
 * @brief Graph::addEdge
 * @param x - first node to be connected
 * @param y - second node to be connected
 * @return true if this node was successfully connetced, false otherwise
 */
bool Graph::addEdge(int x, int y, int distance)
{
    if ((x < 1 || x > numberOfVertices) &&
        (y < 1 || y > numberOfVertices)) {
        return false;
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

void Graph::makeRandomGraph(int density, int minDistance, int maxDistance)
{
    for (graphContainer::iterator iter = graph.begin(); iter != graph.end(); ++iter) {

    }
}

int main()
{
    Graph g = Graph(3);
    g.addEdge(1, 2, 13);
    g.addEdge(2, 1, 6);
    g.addEdge(2, 3, 6);

    g.showGraph();

    return 0;
}
