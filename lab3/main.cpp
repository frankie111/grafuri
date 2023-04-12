#include <iostream>
#include "Graph.h"

int main() {
    Graph g1("../g1.txt");
//    g1.BFS(0);
    g1.printConexComponent();
//    g1.printConexComponentVector();
}
