#ifndef MST_H
#define MST_H

#include <algorithm>
#include <set>

typedef struct edgeList_st
{
    int     from;
    int     to;
    double  distance;
} edgeList;

typedef std::vector<edgeList>  edgeList_t;
typedef std::vector<int>       parentList_t;

class MST
{
private:
    int numberOfVertices;
    int numberOfEdges;
    int mstCost;
    parentList_t parent;
    edgeList_t   edges;

public:
    MST(Graph g);

    int  getMstCost();
    bool edgeExist(int start, int end);
    int  parentOf (int n);
};

#endif // MST_H
