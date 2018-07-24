#include "graph.h"
#include <iostream>
using namespace std;

void testIndegree(Graph& g)
{
        for (int i = 0; i < g.num_verteces; i++) {
                cout << "Indgree of " << i << \
                        " is: "<< g.getInDegree(i) << endl;
        }
}

void testTopSort(Graph& g)
{
        vector<Vertex> top_sort = g.topSort();
        if (top_sort.size() != g.num_verteces) {
                cout << "Graph has a cycle!" << endl;
                return ;
        }
        cout << "Result of Top Sort:" << endl;
        for (int i = 0; i < g.num_verteces; i++) {
                cout << top_sort[i].label << " ";
        }
        cout << endl;
}

int main()
{
        Graph g(6, 8, true);
        g.addEdge(0, 1);
        g.addEdge(1, 2);
        g.addEdge(1, 3);
        g.addEdge(1, 4);
        g.addEdge(2, 5);
        g.addEdge(3, 2);
        g.addEdge(3, 4);
        g.addEdge(4, 5);

        testIndegree(g);
        testTopSort(g);
        g.printGraph();

        return 0;
}
