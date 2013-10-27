#include <iostream>
#include <vector>

using namespace std;

typedef struct edge_st
{
    int     dist;
    struct edge_st* next;
} edge_t;

class Graph
{
public:
    vector<edge_t> graph;

    Graph();
    Graph(int N);
};

Graph::Graph()
{
    graph[0].dist = 0;
    graph[0].next = NULL;
}

Graph::Graph(int N)
{
    edge_t edge;

    for (int i = 0; i < N; i++)
    {
        edge.dist = 1;
        edge.next = NULL;
        graph.push_back(edge);
    }
}

int main()
{


    return 0;
}
