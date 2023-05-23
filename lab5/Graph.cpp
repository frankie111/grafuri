#include "Graph.h"
#include <unordered_map>
#include <set>
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

    unordered_map<string, int> distances;
    for (const auto &e: edgeList) {
        distances[e.city1] = INT_MAX;
        distances[e.city2] = INT_MAX;
    }
    distances[n1] = 0;

    unordered_map<string, string> prev;

    // create a set to store the nodes to visit
    auto cmp = [](const auto &a, const auto &b) { return a.second < b.second; };
    set<pair<string, int>, decltype(cmp)> nodes(cmp);
    nodes.emplace(n1, 0);

    // Djikstra
    while (!nodes.empty()) {
        auto iter = nodes.begin();
        string u = iter->first;
        int du = iter->second;
        nodes.erase(nodes.begin());

        if (u == n2) {
            // reached the end node, print the shortest path and its cost
            cout << "Shortest path from " << n1 << " to " << n2 << ": ";
            string node = n2;
            vector<Edge> path;

            while (node != n1) {
                path.push_back({prev[node], node, distances[node] - distances[prev[node]]});
                node = prev[node];
            }

            for (int i = int(path.size()) - 1; i >= 0; i--) {
                cout << "(" << path[i].city1 << ", " << path[i].city2 << ", " << path[i].weight << ")";
                if (i != 0) cout << " -> ";
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
                    nodes.emplace(e.city2, dv);
                }
            } else if (e.city2 == u) {
                int dv = distances[u] + e.weight;
                if (dv < distances[e.city1]) {
                    distances[e.city1] = dv;
                    prev[e.city1] = u;
                    nodes.emplace(e.city1, dv);
                }
            }
        }
    }

    // end node unreachable
    cout << "There is no path from " << n1 << " to " << n2 << endl;
}
