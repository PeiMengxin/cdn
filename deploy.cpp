#include "deploy.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "graph.h"
#include "myalgorithm.h"

using namespace std;

//你要完成的功能总入口
void deploy_server(char * topo[MAX_EDGE_NUM], int line_num,char * filename)
{

        print_time1("Begin");

//    int consumerNum = 0;
//        char *c;
//        int spaceCount = 0;

//        c = topo[0];

//        while (*c != '\0' && *c != '\n' && *c != '\r')
//        {
//            if (*c == ' ')
//            {
//                c++;
//                spaceCount++;
//                continue;
//            }
//            if (spaceCount == 2)
//            {
//                consumerNum = *c - '0' + consumerNum * 10;
//            }
//            c++;
//        }

//        string res;
//        char a[20];
//        sprintf(a, "%d\n\n",consumerNum);
//        res = a;
//        int netnode, need;

//        for (int i = 1; i < consumerNum+1; i++)
//        {
//            c = topo[line_num-i];
//            netnode = need = spaceCount = 0;
//            while (*c != '\0' && *c != '\n' && *c != '\r')
//            {
//                if (*c == ' ')
//                {
//                    c++;
//                    spaceCount++;
//                    continue;
//                }
//                if (spaceCount == 1)
//                {
//                    netnode = *c - '0' + netnode * 10;
//                }
//                else if (spaceCount == 2)
//                {
//                    need = *c - '0' + need * 10;
//                }
//                c++;
//            }
//            sprintf(a, "%d %d %d",netnode,consumerNum-i,need);
//            res += a;
//            if (i != consumerNum)
//            {
//                res += "\n";
//            }
//        }

//        char * topo_file = (char *)res.c_str();
//        write_result(topo_file, filename);
//    print_time1("End");
//        return;

    stringstream ss;
    int verticesNum = 0;
    int edgeNum = 0;
    int consumernodeNum = 0;

    ss.clear();
    ss<<topo[0];
    ss>>verticesNum>>edgeNum>>consumernodeNum;

    int serverCost = 0;

    ss.clear();
    ss<<topo[2];
    ss>>serverCost;

    //cout<<"serverCost: "<<serverCost<<endl;

    Graph *myGraph = new Graphl(verticesNum);
    myGraph->build(topo, verticesNum, edgeNum);


//    int* low = new int[myGraph->VerticesNum()];
//    bool* keyvertice = new bool[myGraph->VerticesNum()];
//    for (int i = 0;i<myGraph->VerticesNum();i++)
//    {
//        keyvertice[i] = 0;
//    }
//    find_articulation(*myGraph, low, keyvertice);

//    cout<<endl;
//    for (int i = 0;i<myGraph->VerticesNum();i++)
//    {
//        if(keyvertice[i])
//            cout<<i<<" ";

//    }

//    return;

//    cout << "顶点数——" << myGraph->VerticesNum() << endl;
//    cout << "存在边如下——" << endl;
//    for (int i = 0; i < myGraph->VerticesNum(); i++)
//    {
//        for (Edge e = myGraph->FirstEdge(i); myGraph->IsEdge(e); e = myGraph->NextEdge(e))
//        {
//            cout << "from：" << e.from << "  to：" << e.to <<
//                    "   totalBandwidth: " << e.totalBandwidth << "   rend_per: " << e.rend_per<<endl;

//        }
//        cout << endl;
//    }

////    write_result(result_string.data(), filename);

//    int start = 0;
//    int end = 16;

//    std::vector<Record> path;
//    Dijkstra(*myGraph, start, end, path);
//    printPath(path, start, end);

    std::vector<ConsumerNode> consumer;
    int id = -1;
    int from = -1;
    int demand = 0;
    for(int i = 0;i<consumernodeNum;i++)
    {
        ss.clear();
        ss<<topo[i+4+edgeNum+1];
        ss>>id>>from>>demand;
        consumer.push_back(ConsumerNode(id, from, demand));
    }

//    for(size_t i = 0; i<consumer.size();i++)
//    {
//        //ConsumerNode n = consumer[i];
//        cout<< consumer[i] <<endl;
//    }

    std::string result_str = putServerOnEndNode(*myGraph, consumer, serverCost);
    //cout<<result_str<<endl;

    write_result((char *)result_str.c_str(), filename);

        print_time1("End");
}











































