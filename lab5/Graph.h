#ifndef LAB5_GRAPH_H
#define LAB5_GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Edge {
    string city1;
    string city2;
    int weight;
};

class Graph {
private:
    vector<Edge> edgeList;

public:
    explicit Graph(const string& filename);

    void printGraph() const;

    void shortestPath(const string& n1, const string& n2) const;
};

#endif //LAB5_GRAPH_H
