#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    Graph g("../bin.txt");
    bool isBinary =  g.isBinaryTree();
    cout << isBinary << endl;
//    if(isBinary)
//        g.printInOrder(g.matrixToTree());
}
