#include "myalgorithm.h"
#include <assert.h>
#include <time.h>
#include <sys/timeb.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

using namespace std;

std::string putServerOnEndNode(Graph& m_graph, std::vector<ConsumerNode> consumer, int serverCost)
{
    cout<<"putServerOnEndNode"<<endl;

    std::stringstream ss;

    std::string result_str;


    int consumerSize = consumer.size();

    if (consumerSize==0)
    {
        result_str="NA";
        return result_str;
    }

    char buff[32];
    sprintf(buff,"%d\n\n", consumerSize);

    result_str+=buff;

    for (int i = 0; i<m_graph.VerticesNum();i++)
    {
        m_graph.Mark[i] = UNVISITED;
    }

    for (int i = 0; i<consumerSize;i++)
    {
        if (m_graph.Mark[consumer[i].from] == VISITED)
        {
            continue;
        }

        sprintf(buff, "%d %d %d", consumer[i].from, consumer[i].id, consumer[i].demand);

        result_str+=buff;
        if(i<consumerSize - 1)
        {
            result_str+="\n";
        }
    }

    return result_str;

}

void print_time1(const char *head)
{
    struct timeb rawtime;
    struct tm * timeinfo;
    ftime(&rawtime);
    timeinfo = localtime(&rawtime.time);

    static int ms = rawtime.millitm;
    static unsigned long s = rawtime.time;
    int out_ms = rawtime.millitm - ms;
    unsigned long out_s = rawtime.time - s;
    ms = rawtime.millitm;
    s = rawtime.time;

    if (out_ms < 0)
    {
        out_ms += 1000;
        out_s -= 1;
    }
    printf("%s date/time is: %s \tused time is %lu s %d ms.\n", head, asctime(timeinfo), out_s, out_ms);
}




































