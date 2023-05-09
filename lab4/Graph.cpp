#include "Graph.h"
#include <stack>

Graph::Graph(const string &fileName) {
    ifstream file(fileName);

    // Read the number of vertices
    file >> v;

    // Create the adjacency matrix
    adjMatrix.resize(v, vector<int>(v));

    // Read the adjacency matrix from the fileName
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            int tmp;
            file >> tmp;
            adjMatrix[i][j] = tmp;
        }
    }

    file.close();
}

bool Graph::isBinaryTree() const {
    // initialize all parent nodes to -1
    vector<int> parent(v, -1);
    vector<bool> visited(v, false);
    stack<int> s;

    // DFS from 0
    // Mark root as visited, add it to stack
    visited[0] = true;
    s.push(0);

    while (!s.empty()) {
        int cur = s.top();
        s.pop();

        // check each neighbor of the current node
        for (int i = 0; i < v; i++) {
            if (adjMatrix[cur][i]) {
                // if the neighbor has not been visited before, set its parent
                if (!visited[i]) {
                    visited[i] = true;
                    parent[i] = cur;
                    s.push(i);
                }
                    // if the neighbor has already been visited and has a different parent,
                    // then the graph is not a binary tree
                else if (parent[cur] != i) {
                    return false;
                }
            }
        }
    }

    return true;
}

Graph::Node *Graph::matrixToTree() {
    // Create an array to store nodes of the binary tree
    Node *nodes[v];
    for (int i = 0; i < v; i++) {
        nodes[i] = new Node(i);
    }

    // Traverse the adjacency matrix and link the nodes to form a binary tree
    for (int i = 0; i < v; i++) {
        // Find the left and right child of the current node
        int leftChild = -1;
        int rightChild = -1;
        for (int j = 0; j < v; j++) {
            if (adjMatrix[i][j] == 1) {
                if (leftChild == -1) {
                    leftChild = j;
                } else {
                    rightChild = j;
                    break;
                }
            }
        }
        // Link the current node to its children
        if (leftChild != -1)
            nodes[i]->left = nodes[leftChild];
        if (rightChild != -1)
            nodes[i]->right = nodes[rightChild];
    }

    // Return the root of the binary tree
    return nodes[0];
}

void Graph::printInOrder(Node *node) {
    // Traverse tree inorder and print Nodes
    stack<Node *> s;
    Node *curr = node;

    while (!s.empty() || curr != nullptr) {
        if (curr != nullptr) {
            s.push(curr);
            curr = curr->left;
        } else {
            curr = s.top();
            s.pop();
            cout << curr->data << " ";
            curr = curr->right;
        }
    }
}
