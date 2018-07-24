#include <iostream>
#include <vector>
#include <string>
#include "graph.h"

using namespace std;

Vertex::Vertex(int num): label(num)
{
        marked = false;
        path_from = -1;
}

Edge::Edge(int f, int t, double w): \
                from(f), to(t), weight(w)
{
        return ;
}

Graph::Graph(int verteces, int edges, bool directed):\
                num_verteces(verteces), num_edges(edges), directed(directed)
{
        for (int i = 0; i < verteces; i++) {
                Vertex v(i);
                vertex_list.push_back(v);
        }
}

void Graph::addEdge(int from, int to, double weight)
{
        Edge e(from, to, weight);

        vertex_list[from].adj_verts.push_back(e);

        if (!directed) {
                Edge eb(to, from, weight);
                vertex_list[to].adj_verts.push_back(eb);
        }
        return ;
}

void Graph::tranversalGraph(int start_vertex = 0)
{
        if (start_vertex == -1) {
                for (int i = 0; i < vertex_list[start_vertex].adj_verts.size(); i++) {
                        vertex_list[i].marked = true;
                        if (i != start_vertex) {
                                vertex_list[i].path_from = start_vertex;
                        }
                        tranversalGraph(vertex_list[start_vertex].adj_verts[i].to);
                }
        }

        for (int i = 0; i < vertex_list[start_vertex].adj_verts.size(); i++) {
                cout << start_vertex << " -> " << \
                        vertex_list[start_vertex].adj_verts[i].to << endl;
                tranversalGraph(vertex_list[start_vertex].adj_verts[i].to);
        }
        return ;
}

int Graph::getOutDegree(int v)
{
        return vertex_list[v].adj_verts.size();
}

int Graph::getInDegree(int v)
{
        if (!directed) {
                return getOutDegree(v);
        }
        int indegree = 0;
        for (int i = 0; i < vertex_list.size(); i++) {
                for (int j = 0; j < vertex_list[i].adj_verts.size(); j++) {
                        if (vertex_list[i].adj_verts[j].to == v) {
                                indegree ++;
                        }
                }
        }
        return indegree;
}

void Graph::printGraph()
{
        for (int i = 0; i < num_verteces; i++) {
                Vertex vi = vertex_list[i];
                cout << "Node " << vi.label << ": " << endl;
                for (int j = 0; j < vi.adj_verts.size(); j++) {
                        cout << "\t" << vi.adj_verts[j].from \
                                << " -> " << vi.adj_verts[j].to << endl;
                }
        }
}

vector<Vertex> Graph::topSort()
{
        vector<Vertex> Queue;
        vector<Vertex> top_sort_result;
        vector<int> indegrees;

        for (int i = 0; i < num_verteces; i++) {
                int indegree_of_i = getInDegree(i);
                indegrees.push_back(indegree_of_i);
                if (indegree_of_i == 0) {
                        Queue.push_back(vertex_list[i]);
                }
        }

        while (!Queue.empty()) {  // time: |V| + |E|
                Vertex v = Queue.back();
                Queue.pop_back();
                top_sort_result.push_back(Vertex(v.label));
                
                for (int i = 0; i < vertex_list[v.label].adj_verts.size(); i++) {
                        if (--indegrees[vertex_list[v.label].adj_verts[i].to] == 0) {
                                Queue.push_back(vertex_list[v.adj_verts[i].to]);
                        }
                }
        }
        
        if (top_sort_result.size() != num_verteces) {
                cout << "Graph has a Cycle!" << endl;
                return vector<Vertex>();
        }

        return top_sort_result;
}

bool Graph::isCyclic()
{
        vector<Vertex> top_sort = topSort();
        if (top_sort.size() != num_verteces) {
                return false;
        } else {
                return true;
        }
}
