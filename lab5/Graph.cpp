#include "Graph.h"
#include <unordered_map>
#include <queue>

Graph::Graph(const string &filename) {
    ifstream fin(filename);
    string line;
    Edge e;
    while (fin >> e.city1 >> e.city2 >> e.weight)
        edgeList.push_back(e);
    fin.close();
}

void Graph::printGraph() const {
    cout << edgeList.size() << endl;
    for (const auto &e: edgeList)
        cout << e.city1 << " " << e.city2 << " " << e.weight << endl;
}

void Graph::shortestPath(const string &n1, const string &n2) const {
    // create a map to store the distances from the start node to all other nodes
    unordered_map<string, int> distances;
    for (const auto &e: edgeList) {
        distances[e.city1] = INT_MAX;
        distances[e.city2] = INT_MAX;
    }
    distances[n1] = 0;

    // create a priority queue to store the nodes to visit
    auto cmp = [](const auto &a, const auto &b) { return a.second > b.second; };
    priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> pq(cmp);
    pq.emplace(n1, 0);

    // create a map to store the previous node in the shortest path
    unordered_map<string, string> prev;

    // perform Dijkstra's algorithm
    while (!pq.empty()) {
        auto [u, du] = pq.top();
        pq.pop();

        if (u == n2) {
            // reached the end node, print the shortest path and its cost
            cout << "Shortest path from " << n1 << " to " << n2 << ": ";
            string node = n2;
            vector<Edge> path;
            while (node != n1) {
                path.push_back({prev[node], node, distances[node] - distances[prev[node]]});
                node = prev[node];
            }
            for (auto it = path.rbegin(); it != path.rend(); ++it) {
                cout << "(" << it->city1 << ", " << it->city2 << ", " << it->weight << ")";
                if (it != path.rend() - 1) cout << " -> ";
            }
            cout << "\nTotal cost: " << distances[n2] << endl;
            return;
        }

        if (du > distances[u]) continue;

        for (const auto &e: edgeList) {
            if (e.city1 == u) {
                int dv = distances[u] + e.weight;
                if (dv < distances[e.city2]) {
                    distances[e.city2] = dv;
                    prev[e.city2] = u;
                    pq.push({e.city2, dv});
                }
            } else if (e.city2 == u) {
                int dv = distances[u] + e.weight;
                if (dv < distances[e.city1]) {
                    distances[e.city1] = dv;
                    prev[e.city1] = u;
                    pq.push({e.city1, dv});
                }
            }
        }
    }

    // end node was not reached
    cout << "There is no path from " << n1 << " to " << n2 << endl;
}