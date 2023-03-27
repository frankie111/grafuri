#include "Graph.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

Graph::Graph() {

    ifstream f;
    f.open("../data.in");
    f >> n;
    f >> m;
    int x, y;
    for (int i = 0; i < m; i++) {
        f >> x >> y;
        addEdge(x, y);
    }

}

void Graph::matrixToList() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (isEdge(i, j))
                list[i].push_back(j);
        }
    }
}

int Graph::maxOrderMatrix() {
    int max = 0;
    for (int i = 0; i < m; i++) {
        int ct = 0;
        for (int j = 0; j < m; j++)
            if (matrix[i][j] == 1)
                ct++;
        if (ct > max)
            max = ct;
    }

    return max;
}

int Graph::minOrderMatrix() {
    int min = INT_MAX;
    for (int i = 0; i < m; i++) {
        int ct = 0;
        for (int j = 0; j < m; j++)
            if (matrix[i][j] == 1)
                ct++;
        if (ct < min)
            min = ct;
    }

    return min;
}

int Graph::maxOrderList() {
    int max = 0;
    for (int i = 0; i < m; i++) {
        if (list[i].size() > max)
            max = int(list[i].size());
    }

    return max;
}

int Graph::minOrderList() {
    int min = INT_MAX;
    for (int i = 0; i < m; i++) {
        if (list[i].size() < min)
            min = int(list[i].size());
    }

    return min;
}

void Graph::addEdge(int x, int y) {
    matrix[x][y] = 1;
    matrix[y][x] = 1;
}

bool Graph::isEdge(int x, int y) {
    return matrix[x][y] == 1;
}

void Graph::printGraph(bool asMatrix) {
    if (asMatrix)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    else
        for (int i = 0; i < m; i++) {
            vector<int> tmp = list[i];
            cout << i << ": ";
            for (int j: tmp)
                cout << j << ", ";
            cout << endl;
        }
}
