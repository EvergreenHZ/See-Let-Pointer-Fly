#pragma once

#include <vector>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>

#define MYINFINITY 100000
class Graph {
        public:
                bool type;  // true for directed
                cv::Mat adjmat;
        public:
                Graph();  // default directed
                Graph(int num_of_verteces, int type = true);

                bool addEdge(int src, int dst);
                bool deleteEdge(int src, int dst);

                int getIndegree(int target);
                int getOutdegree(int target);

                std::vector<int> topologicalSort();
                void bfs(int);

                std::vector<int> topologicalSortQueue();
                //void bfsQueue();
};
