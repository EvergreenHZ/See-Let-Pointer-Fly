#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <deque>
#include "graph.h"

using namespace std;

Vertex::Vertex(int num): label(num)
{
        marked = false;
        path_from = -1;
        dist = INFINITY_DISTANCE;
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

void Graph::reset()
{
        for (int i = 0; i < num_verteces; i++) {
                vertex_list[i].marked = false;
                vertex_list[i].path_from = -1;
                vertex_list[i].dist = INFINITY_DISTANCE;
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

//void Graph::tranversalGraph(int start_vertex = 0)
//{
//        if (start_vertex == -1) {
//                for (int i = 0; i < vertex_list[start_vertex].adj_verts.size(); i++) {
//                        vertex_list[i].marked = true;
//                        if (i != start_vertex) {
//                                vertex_list[i].path_from = start_vertex;
//                        }
//                        tranversalGraph(vertex_list[start_vertex].adj_verts[i].to);
//                }
//        }
//
//        for (int i = 0; i < vertex_list[start_vertex].adj_verts.size(); i++) {
//                cout << start_vertex << " -> " << 
//                        vertex_list[start_vertex].adj_verts[i].to << endl;
//                tranversalGraph(vertex_list[start_vertex].adj_verts[i].to);
//        }
//        return ;
//}

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
        for (int i = 0; (unsigned int)i < vertex_list.size(); i++) {
                for (int j = 0; (unsigned int)j < (vertex_list[i].adj_verts.size()); j++) {
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
                for (int j = 0; j < (int)vi.adj_verts.size(); j++) {
                        cout << "\t" << vi.adj_verts[j].from \
                                << " -> " << vi.adj_verts[j].to << endl;
                }
        }
}

void Graph::printPath(int terminated_vertex)
{
        if (vertex_list[terminated_vertex].path_from != -1) {
                printPath(vertex_list[terminated_vertex].path_from);
                cout << " -> ";
        }
        //cout << vertex_list[terminated_vertex].label;
        cout << terminated_vertex;
}


bool Graph::isCyclic()
{
        vector<Vertex> top_sort = topSort();
        if (top_sort.size() != (unsigned int)num_verteces) {
                return false;
        } else {
                return true;
        }
}

vector<Vertex> Graph::topSort()
{
        reset();
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
                Vertex v = Queue.front();
                Queue.erase(Queue.begin());
                top_sort_result.push_back(Vertex(v.label));

                for (int i = 0; (unsigned int)i < vertex_list[v.label].adj_verts.size(); i++) {
                        if (--indegrees[vertex_list[v.label].adj_verts[i].to] == 0) {
                                Queue.push_back(vertex_list[v.adj_verts[i].to]);
                        }
                }
        }

        if (top_sort_result.size() !=  (unsigned int)num_verteces) {
                cout << "Graph has a Cycle!" << endl;
                return vector<Vertex>();
        }

        return top_sort_result;
}

void Graph::unweightedShortestPath(int start_vertex)
{
        reset();
        vector<Vertex> Queue;
        vertex_list[start_vertex].dist = 0;

        Queue.push_back(vertex_list[start_vertex]);

        while (!Queue.empty()) {
                Vertex u = Queue.front();
                vertex_list[u.label].marked = true;
                Queue.erase(Queue.begin());

                for (int i = 0; (unsigned int)i < u.adj_verts.size(); i++) {
                        Vertex &w = vertex_list[u.adj_verts[i].to];
                        if (w.dist == INFINITY_DISTANCE) {
                                w.dist = vertex_list[u.label].dist + 1;
                                w.path_from = u.label;
                                Queue.push_back(vertex_list[w.label]);
                        }
                }
        }
}

/*
 * This is a recursion version of dijkstra algo
 * it is Greedy, so it can also solved by Dynamic Programming,
 * which means Recursion is a very natural thought
 */
void Graph::dijkstra(int start_vertex)
{
        static int count = 0;
        if (count == 0) {
                reset();
                vertex_list[start_vertex].dist = 0.0;
        }
        if (++count <= num_verteces) {
                vertex_list[start_vertex].marked = true;
                /* update all vertex adjacent to start_vertex */
                for (unsigned int i = 0; i < vertex_list[start_vertex].adj_verts.size(); i++) {
                        double &dist = vertex_list[vertex_list[start_vertex].adj_verts[i].to].dist;
                        double updated_dist = vertex_list[start_vertex].dist + \
                                              vertex_list[start_vertex].adj_verts[i].weight;
                        if (updated_dist < dist) {
                                dist = updated_dist;
                                vertex_list[vertex_list[start_vertex].adj_verts[i].to].path_from = start_vertex;
                        }
                }

                /* find unmarked vertex with minimum dist */
                double t_dist = INFINITY_DISTANCE;
                unsigned int unmarked_vertex_with_minimum_dist = 0;
                for (unsigned int i = 0; i < vertex_list.size(); i++) {
                        if (!vertex_list[i].marked && t_dist > vertex_list[i].dist) {
                                t_dist = vertex_list[i].dist;
                                unmarked_vertex_with_minimum_dist = i;
                        }
                }
                dijkstra(unmarked_vertex_with_minimum_dist);
        }
}

/* Suppose the graph is connected */
void Graph::primSpanningTree()
{
        //vector<Vertex> Queue;
        static int count = 1;

        if (count == 1) {
                //reset();
                cout << "added Vertex: " << 0 << endl;
                vertex_list[0].marked = true;
        }

        if (++count <= num_verteces) {
                double weight = INFINITY_DISTANCE;
                Edge* min_weight_edge = NULL;

                for (int i = 0; i < num_verteces; i++) {
                        if (vertex_list[i].marked) {
                                vector<Edge> &edges = vertex_list[i].adj_verts;
                                for (unsigned int j = 0; j < edges.size(); j++) {
                                        if (!vertex_list[edges[j].to].marked && \
                                                        weight > edges[j].weight) {
                                                weight = edges[j].weight;
                                                min_weight_edge = &(edges[j]);
                                                vertex_list[edges[j].to].path_from = i;
                                        }
                                }
                        }
                }
                cout << "added Vertex: " << (*min_weight_edge).to << endl;
                vertex_list[(*min_weight_edge).to].marked = true;
                primSpanningTree();
        }

}

//bool Graph::comp(Edge e1, Edge e2)
//{
//        return e1.weight > e2.weight;
//}
//
//void Graph::readEdges(vector<Edge> &edges)
//{
//        bool *readed_flags = new bool[num_verteces][num_verteces];
//
//        for (int i = 0; i < num_verteces; i++) {
//                for (int j = 0; j < num_verteces; j++) {
//                        readed_flags[i][j] = false;
//                }
//        }
//
//        for (int i = 0; i < num_verteces; i++) {
//                Vertex &v = vertex_list[i];
//                
//                for (unsigned int j = 0; j < v.adj_verts.size(); j++) {
//                        int from = v.label;
//                        int to   = v.adj_verts[j].to;
//                        if (!readed_flags[from][to]) {
//                                edges.push_back(v.adj_verts[j]);
//                                readed_flags[from][to] = true;
//                                readed_flags[to][from] = true;
//                        }
//                }
//        }
//}
//
//
//
//Graph* kruscalSpanningTree()
//{
//        static vector<Edge> edges;
//        static int accepted = 0;
//        static int i = 0;
//        if (accepted == 0) {
//                readEdges(edges);
//                sort(edges.begin(), edges.end(), comp);
//        }
//
//        static int same_set[num_verteces];
//        for (int i = 0; i < num_verteces; i++) {
//                same_set[i] = i;
//        }
//
//        static Graph* g = new Graph(num_verteces, 2 *  (num_verteces - 1), false);
//
//        return g;
//}
//
//        //if (accepted < num_verteces) {
//        //        Edge e = edges[i++];
//
//        //        bool &from_marked = vertex_list[e.from].marked;
//        //        bool &to_marked   = vertex_list[e.to].marked;
//
//        //        from_marked = true;
//        //        to_marked   = true;
//
//        //        if (!from_marked && !to_marked) {
//        //                if (e.from < e.to) {
//        //                        same_set[e.to] = e.from;
//        //                } else {
//        //                        same_set[e.from] = e.to;
//        //                }
//        //        } else if (!from_marked && to_marked) {
//        //                same_set[e.from] = e.to;
//        //        } else if (from_marked && !to_marked) {
//        //                same_set[e.to] = e.from;
//        //        } else {
//        //                if (same_set[e.from] == same_set[e.to]) {
//        //                        ;
//        //                } else {
//
