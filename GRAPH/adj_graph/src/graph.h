#pragma once
#include <vector>

class Edge
{
        public:
                // (from, to)
                int from;
                int to;
                double weight;

                Edge(int, int, double);
                bool setFrom(int f) {from = f; return true;}
                bool setTo(int t) { to = t; return true;}
                bool setWeight(double w) { weight = w; return true;}
};

class Vertex 
{
        public:
                int label;
                bool marked;
                int path_from;
                std::vector<Edge> adj_verts;

                Vertex(int);  // label can not be changed, once set.
                void setMarked(bool m) { marked = m;}
                void setPathForm(int previous) { path_from = previous;}
};

class Graph
{
        public:
                int num_verteces;
                int num_edges;
                bool directed;
                std::vector<Vertex> vertex_list;

        public:
                Graph(int, int, bool);

                void addEdge(int, int, double weight = 1.0);  // default 1

                /* Graph Info */
                int getInDegree(int);

                int getOutDegree(int);

                bool isConnected();  // the whole graph is connected

                bool isConnected(int, int);  // u, v is connected, distanceBetween(...)

                bool isCyclic();  // if G is cyclic

                bool isTree();  // judge if G is a tree

                double distanceBetween(int, int);  // u, v minimum distance

                /* top sort */
                std::vector<Vertex> topSort();

                /* Search Graph */
                void dfs(int start_vertex = 0);  // default 0

                void bfs(int start_vertex = 0);  // default 0

                /* Spanning Tree Algo */
                Graph primSpanningTree();

                Graph kruscalSpanningTree();

                Graph dfsSpanningTree();

                Graph bfsSpanningTree();

                Graph transposeGraph();

                /* display */
                void printGraph();

                void tranversalGraph(int);  // default 0

                bool saveGraph();  // save to file, use C style
};
