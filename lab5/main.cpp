#include <iostream>
#include "Graph.h"

int main() {
    Graph g("../Graph.txt");
//    g.printGraph();

    g.shortestPath("Sibiu", "Suceava");
}
