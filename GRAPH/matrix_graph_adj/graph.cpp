#include <iostream>
#include <vector>
#include "graph.h"
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>

using namespace std;
using namespace cv;

Graph::Graph()
{
        type = true;  // for directed graph
}

Graph::Graph(int num_of_verteces, int type): \
                adjmat(num_of_verteces, num_of_verteces, CV_8UC1), type(type) {}

bool Graph::addEdge(int src, int dst)
{
        if (src > adjmat.rows ||
                        dst > adjmat.rows ||
                        src < 0           ||
                        dst < 0) { return false;}

        if (type) {
                adjmat.at<unsigned char>(src, dst) = 1;
        } else {  // undirected
                adjmat.at<unsigned char>(src, dst) = 1;
                adjmat.at<unsigned char>(dst, src) = 1;
        }

        return true;
}

bool Graph::deleteEdge(int src, int dst)
{
        if (src > adjmat.rows ||
                        dst > adjmat.rows ||
                        src < 0           ||
                        dst < 0) { return false;}
        if (type) {
                adjmat.at<unsigned char>(src, dst) = 0;
        } else {  // undirected
                adjmat.at<unsigned char>(src, dst) = 0;
                adjmat.at<unsigned char>(dst, src) = 0;
        }

        return true;
}

int Graph::getIndegree(int target)
{
        int count = 0;
        for (int i = 0; i < adjmat.rows; i++) {
                if (adjmat.at<unsigned char>(i, target)) {
                        count++;
                }
        }
        return count;
}

int Graph::getOutdegree(int target)
{
        int count = 0;
        for (int i = 0; i < adjmat.rows; i++) {
                if (adjmat.at<unsigned char>(target, i)) {
                        count ++;
                }
        }
        return count;
}

vector<int> Graph::topologicalSort()
{
        vector<int> topnum;
        vector<int> indegrees;
        vector<bool> flags;
        for (int i = 0; i < adjmat.rows; i++) {
                indegrees.push_back(getIndegree(i));
                flags.push_back(true);
        }

        int found = -1;
        for (int i = 0; i < adjmat.rows; i++) {
                found = -1;
                for (int j = 0; j < adjmat.rows; j++) {  // check all verteces
                        if (indegrees[j] == 0 && flags[j]) {
                                topnum.push_back(j);
                                flags[j] = false;
                                found = j;
                                break;
                        }
                }
                if (found == -1) {
                        cout << "There is a cycle" << endl;
                        exit(-1);
                }
                // update indegrees
                for (int k = 0; k < adjmat.rows; k++) {
                        if (adjmat.at<unsigned char>(found, k)) {
                                indegrees[k]--;
                        }
                }
        }
        return topnum;
}

vector<int> Graph::topologicalSortQueue()
{
        vector<int> queue;
        vector<int> topnum;
        vector<int> indegrees;
        for (int i = 0; i < adjmat.rows; i++) {
                int num_of_indegree = getIndegree(i);
               if (num_of_indegree  == 0) {
                       queue.push_back(i);
               }
               indegrees.push_back(num_of_indegree);
        }
        while(!queue.empty()) {
                int out_num = queue[0];
                topnum.push_back(out_num);
                queue.erase(queue.begin());

                // update states
                for (int i = 0; i < adjmat.rows; i++) {
                        if (adjmat.at<unsigned char>(out_num, i)) {
                                if (--indegrees[i] == 0) {
                                        queue.push_back(out_num);
                                }
                        }
                }
        }
        return topnum;
}

void Graph::bfs(int source)
{
        vector<bool> known;
        vector<int> dist;
        vector<int> verteces;
        //vector<int> p
        //init table
        for (int i = 0; i < adjmat.rows; i++) {
                known.push_back(false);
                dist.push_back(MYINFINITY);
                verteces.push_back(i);
        }
        dist[source] = 0;
        for (int current_dist = 0; current_dist < adjmat.rows; current_dist++) {
                for (int i = 0; i < adjmat.rows; i++) {
                        if (dist[i] == current_dist && known[i] == false) {
                                known[i] = true;
                                cout << i << " ";
                                for (int k = 0; k < adjmat.rows; k++) {
                                        if (adjmat.at<unsigned char>(i, k)) {
                                                dist[k] = current_dist + 1;
                                        }
                                }
                        }
                }
        }
}
