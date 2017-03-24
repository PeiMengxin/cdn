#ifndef __GRAPH_H
#define __GRAPH_H

#define UNVISITED 0
#define VISITED 1
#define MY_INFINITY 99999999
#define ROOT -1

#include <iostream>
#include <sstream>
#include <fstream>
#include "LList.h"
#include "minheap.h"
#include <queue>

class ConsumerNode
{
public:
    ConsumerNode();
    ConsumerNode(int _id, int f, int d);

    friend std::ostream& operator<<(std::ostream& os, const ConsumerNode& n);

    int id;
    int from;
    int demand;

    ~ConsumerNode();
};


class Record
{
public:
    int pre;
    int cost;
    Record();
    Record(int p, int c);
    ~Record();

private:

};

class Edge
{
public:
    int from, to, weight, totalBandwidth, rend_per, useBandwidth;
    Edge();
    Edge(int f, int t, int w, int totalBandwidth = 0,int rend_per = 0);
    bool operator >(Edge oneEdge);
    bool operator <(Edge oneEdge);
};

class Graph
{
public:
    int numVertex;
    int numEdge;
    int *Mark;
    int *Indegree;
    Graph(int numVert);
    ~Graph();

    virtual Edge FirstEdge(int oneVertex) = 0;
    virtual Edge NextEdge(Edge preEdge) = 0;
    int VerticesNum();
    int EdgesNum();
    bool IsEdge(Edge oneEdge);
    int FromVertex(Edge oneEdge);
    int ToVertex(Edge oneEdge);
    int Weight(Edge oneEdge);

    virtual void setEdge(int from, int to, int weight) = 0;
    virtual void setEdge(int from, int to, int weight, int totalBandwidth, int rend_per) = 0;
    virtual void delEdge(int from, int to) = 0;
    virtual void build(char * topo[], int verticesNum, int edgeNum) = 0;
};

struct listUnit
{
    int vertex;
    int weight;

    int totalBandwidth;
    int rend_per;
    int useBandwidth;
};

class Graphl : public Graph
{
    friend class Graphdup;

private:
    LList<listUnit> *graList;

public:
    Graphl(int numVert);
    ~Graphl();

    Edge FirstEdge(int oneVertex);
    Edge NextEdge(Edge preEdge);
    void setEdge(int from, int to, int weight);
    void setEdge(int from, int to, int weight, int totalBandwidth, int rend_per);
    void delEdge(int from, int to);
    void build(char * topo[], int verticesNum, int edgeNum);

};

#endif // __GRAPH_H
