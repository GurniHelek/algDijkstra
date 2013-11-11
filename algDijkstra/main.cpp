// *************************************************************************
// ******** Homework 2: Implement Dijkstra's Algorithm *********************
// *************************************************************************

#include "graph.h"
#include "shortestpath.h"
#include "mst.h"

/**
 * @brief test - average path length calculation
 * @param density - density of graph to be randomly generated
 * @param numberOfNodes - number of nodes in graph to be randomly generated
 * @return average path length from start node to all others nodes
 */
double test(double density, int numberOfNodes)
{
    Graph graph = Graph(numberOfNodes);
    graph.makeRandomGraph(density, MIN_DISTANCE, MAX_DISTANCE);

    ShortestPath path = ShortestPath(graph, 1);
    int pathCounter = 0;
    double pathSize = 0;
    double pathSum  = 0;

    for (int i = 2; i <= numberOfNodes; i++) {
        pathSize = path.getPathSize(i);

        if (pathSize) {
            pathCounter++;
            pathSum += pathSize;
        }
    }

    return (pathSum/(double)pathCounter);
}

int main()
{
    srand (time(NULL));

    double density;
    int    numberOfNodes = 50;

    density = 0.2;
    std::cout << "TEST 1 :: For graph with " << numberOfNodes
              << " nodes and density " << density
              << " average path length is " << test(density, numberOfNodes) << std::endl;

    density = 0.4;
    std::cout << "TEST 2 :: For graph with " << numberOfNodes
              << " nodes and density " << density
              << " average path length is " << test(density, numberOfNodes) << std::endl;


    const char* filename = "../SampleTestData_mst_data.txt";
    Graph g = Graph(filename);
    std::cout << "TT " << g.getNumberOfVertices() << std::endl;

    MST mst = MST(g);

    std::cout << "The cost of minimum spanning tree is " << mst.getMstCost() << std::endl;

    return 0;
}
