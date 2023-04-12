#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

Graph::Graph() = default;

Graph::Graph(const string &fileName) {
    std::ifstream file(fileName);

    file >> nodes;
    file >> edges;
    adjacencyList.resize(nodes);

    for(int i = 0; i <  edges; i++){
        int node, connectedNode;
        file >> node >> connectedNode;
        adjacencyList[node].push_back(connectedNode);
        adjacencyList[connectedNode].push_back(node);
    }

    file.close();
}

Graph::Graph(const Graph &other) {
    nodes = other.nodes;
    edges = other.edges;
    adjacencyList = other.adjacencyList;
}

void Graph::text() {
    for(int i = 0; i < nodes; i++){
        cout << i << ": ";
        for(int j : adjacencyList[i]){
            cout << j << " ";
        }
        cout << endl;
    }
}

void Graph::BFS(int start) {
    vector<bool> visited(nodes, false);
    queue<int> queue;

    visited[start] = true;
    queue.push(start);

    while(!queue.empty()){
        int node = queue.front();
        cout << node << " ";
        queue.pop();

        for(int i : adjacencyList[node]){
            if(!visited[i]){
                visited[i] = true;
                queue.push(i);
            }
        }
    }
}

int Graph::weg(int start, int stop) {
    vector<bool> visited(nodes, false);
    vector<int> distance(nodes, 0);
    deque<int> queue;

    queue.push_back(start);
    visited[start] = true;
    distance[start] = 0;

    while(!queue.empty()){
        int node = queue.front();
        queue.pop_front();

        if(node == stop){
            return distance[node];
        }

        for(auto i : adjacencyList[node]){
            if(!visited[i]){
                queue.push_back(i);
                distance[i] = distance[node] + 1;
                visited[i] = true;
            }
        }
    }
    cout << endl;

    cout << "No way between " << start << " and " << stop << endl;
    return -1;
}