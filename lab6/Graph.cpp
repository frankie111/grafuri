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


string Graph::findNextNeighbor(const string &currentNode, vector<string> &visitedNodes) {
    int minWeight = INT_MAX;
    string nextNode;

    // Find the neighbor with the minimum weight that hasn't been visited yet
    for (const Edge &edge: edgeList) {
        if ((edge.city1 == currentNode || edge.city2 == currentNode) && edge.weight < minWeight) {
            string neighbor = (edge.city1 == currentNode) ? edge.city2 : edge.city1;
            if (find(visitedNodes.begin(), visitedNodes.end(), neighbor) == visitedNodes.end()) {
                minWeight = edge.weight;
                nextNode = neighbor;
            }
        }
    }

    return nextNode;
}

void Graph::printHamiltonKreis(const string &n1) {
    vector<string> visitedNodes;
    vector<string> cycle;
    int totalCost = 0;

    // Start the cycle from node n1
    string currentNode = n1;
    visitedNodes.push_back(currentNode);
    cycle.push_back(currentNode);

    // Find the next neighbor using the nearest neighbor heuristic until all nodes are visited
    while (visitedNodes.size() < edgeList.size()) {
        string nextNode = findNextNeighbor(currentNode, visitedNodes);
        visitedNodes.push_back(nextNode);
        cycle.push_back(nextNode);

        // Calculate the weight of the edge and add it to the total cost
        for (const Edge &edge: edgeList) {
            if ((edge.city1 == currentNode && edge.city2 == nextNode) ||
                (edge.city1 == nextNode && edge.city2 == currentNode)) {
                totalCost += edge.weight;
                break;
            }
        }

        if (!nextNode.empty())
            currentNode = nextNode;
    }

    // Calculate the weight of the last edge that completes the cycle
    Edge lastEdge;
    for (const Edge &edge: edgeList) {
        if ((edge.city1 == currentNode && edge.city2 == n1) || (edge.city1 == n1 && edge.city2 == currentNode)) {
            totalCost += edge.weight;
            lastEdge = edge;
            break;
        }
    }

    cout << "Cost: " << totalCost << endl;

    // Print the edges that form the cycle along with their weights
    cout << "Edges:" << endl;
    int n = (int) cycle.size();
    for (int i = 0; i < n; i++) {
        string current = cycle[i];
        string next = cycle[(i + 1) % n];

        for (const Edge &edge: edgeList) {
            if ((edge.city1 == current && edge.city2 == next) || (edge.city1 == next && edge.city2 == current)) {
                cout << "(" << edge.city1 << " - " << edge.city2 << ") Weight: " << edge.weight << endl;
                break;
            }
        }
    }

    cout << "(" << lastEdge.city1 << " - " << lastEdge.city2 << ") Weight: " << lastEdge.weight << endl;
}

