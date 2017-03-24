#include "graph.h"
using namespace std;
using std::cout;

bool Edge::operator<(Edge oneEdge)
{
    return weight < oneEdge.weight;
}

bool Edge::operator>(Edge oneEdge)
{
    return weight > oneEdge.weight;
}

Edge::Edge(int f, int t, int w, int totalBandwidth/* = 0*/, int rend_per/* = 0*/)
{
    from = f;
    to = t;
    weight = w;
    this->totalBandwidth = totalBandwidth;
    this->rend_per = rend_per;
    this->useBandwidth = 0;
}

Edge::Edge()
{
    from = -1;
    to = -1;
    weight = 0;
    totalBandwidth = 0;
    rend_per = 0;
    useBandwidth = 0;
}

Graph::Graph(int numVert)
{
    numVertex = numVert;
    numEdge = 0;
    Indegree = new int[numVertex];
    Mark = new int[numVertex];

    for (int i=0;i<numVertex;i++)
    {
        Mark[i] = UNVISITED;
        Indegree[i] = 0;
    }
}

Graph::~Graph()
{
    delete[] Mark;
    delete[] Indegree;
}

int Graph::VerticesNum()
{
    return numVertex;
}

int Graph::EdgesNum()
{
    return numEdge;
}

bool Graph::IsEdge(Edge oneEdge)
{
    if (oneEdge.weight > 0 && oneEdge.weight < MY_INFINITY&&oneEdge.to >= 0)
        return true;
    else
        return false;
}

int Graph::FromVertex(Edge oneEdge)
{
    return oneEdge.from;
}

int Graph::Weight(Edge oneEdge)
{
    return oneEdge.weight;
}

int Graph::ToVertex(Edge oneEdge)
{
    return oneEdge.to;
}

Graphl::Graphl(int numVert) :Graph(numVert)
{
    graList = new LList<listUnit>[numVertex];
}

Graphl::~Graphl()
{
    delete[] graList;
}

Edge Graphl::FirstEdge(int oneVertex)
{
    Edge myEdge;
    myEdge.from = oneVertex;
    Link<listUnit> *temp = graList[oneVertex].head;

    if (temp->next!=NULL)
    {
        myEdge.to = temp->next->element.vertex;
        myEdge.weight = temp->next->element.weight;
        myEdge.totalBandwidth = temp->next->element.totalBandwidth;
        myEdge.rend_per = temp->next->element.rend_per;
        myEdge.useBandwidth = temp->next->element.useBandwidth;
    }

    return myEdge;
}

Edge Graphl::NextEdge(Edge preEdge)
{
    Edge myEdge;
    myEdge.from = preEdge.from;
    Link<listUnit> *temp = graList[preEdge.from].head;

    while (temp->next!=NULL && temp->next->element.vertex<=preEdge.to)
    {
        temp=temp->next;
    }

    if (temp->next!=NULL)
    {
        myEdge.to = temp->next->element.vertex;
        myEdge.weight = temp->next->element.weight;
        myEdge.totalBandwidth = temp->next->element.totalBandwidth;
        myEdge.rend_per = temp->next->element.rend_per;
        myEdge.useBandwidth = temp->next->element.useBandwidth;
    }

    return myEdge;
}

void Graphl::build(char *topo[], int verticesNum, int edgeNum)
{
    int node_start_line = 4;
    int from,to,totalBandwidth,rend_per = -1;
    int weight = 1;
    stringstream ss;
    for(int i = 0;i<edgeNum;i++)
    {
        ss.clear();
        ss<<topo[i+node_start_line];
        ss>>from>>to>>totalBandwidth>>rend_per;
        weight = totalBandwidth*rend_per;
        //cout<<from<<" "<<to<<" "<<totalBandwidth<<" "<<rend_per<<endl;
        if (from >= 0 && to >= 0 && totalBandwidth > 0 && rend_per >= 0 && from < verticesNum && to < verticesNum)
        {
            setEdge(from, to, weight, totalBandwidth, rend_per);
            setEdge(to, from, weight, totalBandwidth, rend_per);
        }
    }
}

void Graphl::setEdge(int from, int to, int weight)
{
    Link<listUnit> *temp = graList[from].head;
    while (temp->next!=NULL && temp->next->element.vertex<=to)
    {
        temp=temp->next;
    }

    if (temp->next==NULL)
    {
        temp->next = new Link < listUnit > ;
        temp->next->element.vertex = to;
        temp->next->element.weight = weight;

        numEdge++;
        Indegree[to]++;
        return;
    }
    if (temp->next->element.vertex == to)
    {
        temp->next->element.weight = weight;

        return;
    }

    if (temp->next->element.vertex > to)
    {
        Link<listUnit> *other = temp->next;
        temp->next = new Link < listUnit > ;
        temp->next->element.vertex = to;
        temp->next->element.weight = weight;

        temp->next->next = other;
        numEdge++;
        Indegree[to]++;
    }
}

void Graphl::setEdge(int from, int to, int weight, int totalBandwidth, int rend_per)
{
    Link<listUnit> *temp = graList[from].head;
    while (temp->next!=NULL && temp->next->element.vertex<=to)
    {
        temp=temp->next;
    }

    if (temp->next==NULL)
    {
        temp->next = new Link < listUnit > ;
        temp->next->element.vertex = to;
        temp->next->element.weight = weight;
        temp->next->element.totalBandwidth = totalBandwidth;
        temp->next->element.rend_per = rend_per;
        numEdge++;
        Indegree[to]++;
        return;
    }
    if (temp->next->element.vertex == to)
    {
        temp->next->element.weight = weight;
        temp->next->element.totalBandwidth = totalBandwidth;
        temp->next->element.rend_per = rend_per;
        return;
    }

    if (temp->next->element.vertex > to)
    {
        Link<listUnit> *other = temp->next;
        temp->next = new Link < listUnit > ;
        temp->next->element.vertex = to;
        temp->next->element.weight = weight;
        temp->next->element.totalBandwidth = totalBandwidth;
        temp->next->element.rend_per = rend_per;
        temp->next->next = other;
        numEdge++;
        Indegree[to]++;
    }
}

void Graphl::delEdge(int from, int to)
{
    Link<listUnit> *temp = graList[from].head;
    while (temp->next!=NULL && temp->next->element.vertex<to)
    {
        temp=temp->next;
    }

    if (temp->next == NULL)
        return;
    if (temp->next->element.vertex == to)
    {
        Link<listUnit> *other = temp->next->next;
        delete temp->next;
        temp->next = other;
        numEdge--;
        Indegree[to]--;
    }
}

Record::~Record()
{

}

Record::Record()
{
    pre = -1;
    cost = MY_INFINITY;
}

Record::Record(int p, int c)
{
    pre = p;
    cost = c;
}

ConsumerNode::ConsumerNode()
{
    id = -1;
    from = -1;
    demand = -1;
}

ConsumerNode::ConsumerNode(int _id, int f, int d)
{
    id = _id;
    from = f;
    demand = d;
}

std::ostream& operator<<(std::ostream& os, const ConsumerNode& n)
{
    os<<"id="<<n.id<<" from:"<<n.from<<" demand:"<<n.demand;
    return os;
}

ConsumerNode::~ConsumerNode()
{

}
