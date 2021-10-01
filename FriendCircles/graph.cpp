#include "graph.h"

#include <stack>
#include <queue>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

bool DFS(Node* start, Node* end) {
    stack<Node*> u;
    u.push(start);
    while (u.size() != 0){
        Node* temp = u.top();
        if (temp == end){
            return true;
        }
        u.pop();
        for (size_t i = 0; i < temp -> neighbors.size(); i++){
            if (!temp -> visited){
                temp -> visited = true;
            u.push(temp -> neighbors[i]);
            }
        }
    }
	return false;
}

bool BFS(vector<vector<int> > adjacency_matrix, int start, int end) {
    queue<int> u;
    u.push(start);
    set<int> isVisited;
    while (u.size() != 0){
        int temp = u.front();
        if (temp == end){return true;}
        isVisited.insert(temp);
        for (size_t i = 0; i < adjacency_matrix.size(); i++){//for all neighbors
            if (adjacency_matrix[temp][i] == 1){//making sure its a neighbor
                if (isVisited.find(i) == isVisited.end()){//for a* be sure to skip visited nodes after popping
                    if (i == end){return true;}//for dijkstra's push all nodes with lower h 
                    u.push(i);}

            }
        }
       u.pop();
    }
	return false;
}
