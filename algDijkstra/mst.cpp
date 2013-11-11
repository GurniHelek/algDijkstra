#include "graph.h"
#include "mst.h"

bool cmp (edgeList p, edgeList q)
{
    if ( p.distance < q.distance ) return true;
    return false;
}

bool MST::edgeExist(int start, int end)
{
    for (unsigned int i = 0; i < edges.size(); i++) {
        if (edges[i].from == start && edges[i].to == end) {
            return true;
        }
    }
    return false;
}

int MST::parentOf(int n)
{
    if (n == parent [n]) return n;
    return parent [n] = parentOf (parent [n]);
}

MST::MST(Graph graph)
{
    int numberOfVertices = graph.getNumberOfVertices();
    int numberOfEdges    = graph.getNumberOfEdges();

    mstCost = 0;
    parent.clear();
    parent.resize(numberOfVertices);
    edges.clear();
    edges.resize(0);

    for ( int i = 0; i < numberOfVertices; i++ )
        parent [i] = i;

    graph_t g = graph.getGraph();
    for (graph_t::iterator iter = g.begin(); iter != g.end(); ++iter) {
        for (int i = (*iter).first; i <= numberOfVertices; i++) {

            if (graph.isAdjacent((*iter).first, i)) {
                int start, end;
                if ((*iter).first > i) {
                    start = i;
                    end   = (*iter).first;
                }
                else {
                    end   = i;
                    start = (*iter).first;
                }

                if (!edgeExist(start, end)) {
                    edge ed;
                    graph.getEdge(ed, start, end);
                    edgeList e = {start-1, end-1, ed.distance};
                    edges.push_back(e);
                }
            }
        }
    }

    std::sort (edges.begin(), edges.end(), cmp);

    int selectedEdges = edges.size() - 1;

    for ( int i = 0; i < numberOfEdges && selectedEdges; i++ ) {
        int p = parentOf (edges[i].from);
        int q = parentOf (edges[i].to);

        if ( p != q ) {
            parent [p] = q;
            selectedEdges--;
            mstCost += edges[i].distance;
        }
    }
}

int MST::getMstCost()
{
    return mstCost;
}

