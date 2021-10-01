//
//  main.cpp
//  1500-cyclicComponents
//
//  Created by Zaid Abdulrehman on 7/31/21.
//  Copyright © 2021 Zaid Abdulrehman. All rights reserved.
//

#include <iostream>


int main(int argc, const char * argv[]) {
    long long int numberOfVertices = 0;
    long long int numberOfEdges = 0;
    long long int u = 0;
    long long int v = 0;
    std::cout << "Hello, World!\n";
    std::cin >> numberOfVertices;
    std::cin >> numberOfEdges;
    //build the graph
    //instantiate graph
    bool** graph = new bool*[numberOfVertices];
    for (long long int i = 0; i < numberOfVertices; i++){
        graph[i] = new bool[numberOfVertices];
        for (long long int c = 0; c < numberOfVertices; c++){
            graph[i][c] = false;
        }
    }
    //populate matrix
    for (long long int i = 0; i < numberOfEdges; i++){
        std::cin >> u;
        std::cin >> v;
        graph[u][v] = true;
        graph[v][u] = true;
    }
    //our graph has been built
    
    /*
     
     to detect a connected component, we will simply group all vertices found in a dfs, if during the dfs, a vertex is visited more than once, the edges of all vertices in the connected component must have been visited-if this is true, we have a cycle. So, one simple way to check this is to make sure that each vertex has a degree of 2. The found vertices will be ignored when searching for further connected components
     
        start at a vertex, if the vertex has been visited, move to the next available component. Otherwise, if it has more than one neighbor or 0 neighbors, mark the connected component a non-cycle. Remove the vertex from the graph by setting the corresponding column and row to false. Continue the DFS.
     
     **/
    
    
    return 0;
}
