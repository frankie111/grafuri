//
// Created by Mircea on 4/7/2023.
//

#include "Graph.h"
#include <fstream>
#include <queue>

Graph::Graph(const string &filename) {
    ifstream f;
    f.open(filename);
    f >> n;
    f >> m;

    for (int i = 0; i < m; i++) {
        pair<int, int> tmp{};
        f >> tmp.first;
        f >> tmp.second;

        edge_list.push_back(tmp);
    }
}

vector<int> Graph::getNeighbours(int _n) const {
    vector<int> neighbours{};
    for (const auto &edge: edge_list) {
        if (edge.first == _n)
            neighbours.push_back(edge.second);
        else if (edge.second == _n)
            neighbours.push_back(edge.first);
    }

    return neighbours;
}

void Graph::BFS(int x) const {
    vector<bool> visited(n, false);
    queue<int> q;

    //mark root as visited and add it to queue
    visited[x] = true;
    q.push(x);

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current + 1 << " ";

        for (int neighbour: getNeighbours(current)) {
            if (!visited[neighbour]) {
                visited[neighbour] = true;
                q.push(neighbour);
            }
        }
    }
}

void Graph::BFS(int x, vector<bool> &visited, bool print) const {
    queue<int> q;

    //mark root as visited and add it to queue
    visited[x] = true;
    q.push(x);

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        if (print)
            cout << current + 1 << " ";

        for (int neighbour: getNeighbours(current)) {
            if (!visited[neighbour]) {
                visited[neighbour] = true;
                q.push(neighbour);
            }
        }
    }
}

//void Graph::printConexComponentVector() const {
//    //initialize visited with 0
//    vector<bool> visited(n, false);
//    vector<vector<int>> components;
//
//    for (int i = 0; i < n; i++) {
//        if (!visited[i]) {
//            vector<int> component;
//            BFS(i, visited, component);
//            components.push_back(component);
//        }
//    }
//
//    cout << "Total number of components = " << components.size() << endl;
//
//    for (int i = 0; i < components.size(); i++) {
//        cout << "component " << i + 1 << ":\n";
//        for (int v: components[i])
//            cout << v << ' ';
//        cout << "\n\n";
//    }
//}

void Graph::printConexComponent() const {
    //initialize visited with 0
    vector<bool> visited(n, false);
    int comp_count = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            comp_count++;
            //traverse without printing
            BFS(i, visited, false);
        }
    }

    cout << "Total number of components = " << comp_count << endl;

    visited = vector<bool>(n, false);
    int ct = 1;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            //traverse and print
            cout << "Component " << ct << ":\n";
            ct++;
            BFS(i, visited, true);
            cout << endl;
        }
    }

}
