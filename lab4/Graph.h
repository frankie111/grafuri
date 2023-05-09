#ifndef LAB4_GRAPH_H
#define LAB4_GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Graph {
private:
    vector<vector<int>> adjMatrix;
    int v{};

    struct Node {
        int data;
        Node *left{nullptr};
        Node *right{nullptr};

        explicit Node(int val) : data{val} {};
    };

public:
    explicit Graph(const string &fileName);

    [[nodiscard]] bool isBinaryTree() const;

    static void printInOrder(Node *node);

    Node *matrixToTree();

};

#endif //LAB4_GRAPH_H