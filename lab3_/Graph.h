#ifndef LAB3_GRAPH_H
#define LAB3_GRAPH_H

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Graph {
private:
    int vertices{}; //number of vertices
    int edges{}; //number of edges
    vector<vector<int>> adj_list{};
    vector<pair<int, int>> edge_list{};
    vector<vector<int>> adj_matrix{};

public:
    Graph();

    explicit Graph(vector<vector<int>> &adj_list, int edges, int vertices);

    explicit Graph(const string &filename);

    static Graph makeFromMatrix(vector<vector<int>> &adjacency_matrix, int edges, int vertices);

    static Graph makeFromEdgeList(vector<pair<int, int>> &edge_list, int edges, int vertices);


    //Edge list methods:
    void readEdgeList(const string &file);

    void printEdgeList() const;

    void printNeighbouringVerticesEL(int _v) const;

    [[nodiscard]] bool isEdgeInGraphEL(const pair<int, int> &edge) const;

    [[nodiscard]] bool isVertexInGraphEL(int _v) const;

    //adjacency list

    void BFS(int s) const;

    void DFS(int s) const;

    //adjacency matrix

    void BFS_AM(int s) const;

    void DFS_AM(int s) const;

    [[nodiscard]] int weg_len(int start, int stop) const;

    void weg(int start, int stop) const;
};


#endif //LAB3_GRAPH_H
