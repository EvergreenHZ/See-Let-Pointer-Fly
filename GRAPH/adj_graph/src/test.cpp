#include "graph.h"
#include <iostream>
using namespace std;

Graph* generateWeightedDirectedGraph()
{
        Graph* g = new Graph(8, 11, true);
        g->addEdge(0, 1, 1);
        g->addEdge(0, 2, 4);
        g->addEdge(0, 3, 7);
        g->addEdge(1, 2, 1);
        g->addEdge(1, 4, 2);
        g->addEdge(2, 3, 2);
        g->addEdge(2, 5, 5);
        g->addEdge(3, 6, 3);
        g->addEdge(4, 5, 3);
        g->addEdge(5, 7, 3);
        g->addEdge(6, 7, 1);

        return g;
}

Graph* generateUnweightedDirectedGraph()
{
        Graph* g = new Graph(6, 16, false);
        g->addEdge(0, 1);
        g->addEdge(1, 2);
        g->addEdge(1, 3);
        g->addEdge(1, 4);
        g->addEdge(2, 5);
        g->addEdge(3, 2);
        g->addEdge(3, 4);
        g->addEdge(4, 5);

        return g;
}


void infoGraph(Graph& g)
{
        cout << "Label  |  Known  |  Dist  |  Pv" << endl;
        for (int i = 0; i < g.num_verteces; i++) {
                Vertex v = g.vertex_list[i];
                cout << v.label << "\t\t" << v.marked \
                        << "\t\t" << v.dist << "\t" << v.path_from << endl;
        }
}

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
        if (top_sort.size() != (unsigned int)g.num_verteces) {
                cout << "Graph has a cycle!" << endl;
                return ;
        }
        cout << "Result of Top Sort:" << endl;
        for (int i = 0; i < g.num_verteces; i++) {
                cout << top_sort[i].label << " ";
        }
        cout << endl;
}

void testUnweightedShortestPath(Graph& g, int start_vertex = 0, int terminated_vertex = 2)
{
        g.unweightedShortestPath(start_vertex);
        while (g.vertex_list[terminated_vertex].path_from != -1) {
                cout << terminated_vertex << " <- ";
                terminated_vertex = g.vertex_list[terminated_vertex].path_from;
        }
        cout << start_vertex << endl;
}

void testDijkstra(Graph &g, int start_vertex = 0)
{
        g.dijkstra(start_vertex);

        int terminated_vertex = 7;
        while (g.vertex_list[terminated_vertex].path_from != -1) {
                cout << terminated_vertex << " <- ";
                terminated_vertex = g.vertex_list[terminated_vertex].path_from;
        }
        cout << start_vertex << endl;

        infoGraph(g);
        g.printPath(7);
        cout << endl;
}

void testPrimAlgo(Graph &g)
{
        g.primSpanningTree();
        infoGraph(g);
}
        
void testUnweightedGraph()
{
        Graph *g = generateUnweightedDirectedGraph();
        (*g).printGraph();
        //infoGraph(*g);
        testPrimAlgo(*g);
        //infoGraph(*g);
        //testIndegree(*g);
        //testTopSort(*g);
        //testUnweightedShortestPath(*g);
        //infoGraph(*g);
        //g->printGraph();


        if (!g) {
                free(g);
        }
}

void testWeightedGraph()
{
        Graph* g = generateWeightedDirectedGraph();

        testDijkstra(*g);

        if (!g) {
                free(g);
        }
}


int main()
{
        //testWeightedGraph();
        testUnweightedGraph();
        return 0;
}
