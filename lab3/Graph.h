#ifndef LAB3_GRAPH_H
#define LAB3_GRAPH_H

#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    int n{}; //number of vertices
    int m{}; //number of edges
    vector <pair<int, int>> edge_list{};

public:
    explicit Graph(const string &filename);

    [[nodiscard]] vector<int> getNeighbours(int _n) const;

    void BFS(int x, vector<bool> &visited, bool print) const;

    void BFS(int x) const;

    void printConexComponentVector() const;

    void printConexComponent() const;

};


#endif //LAB3_GRAPH_H
