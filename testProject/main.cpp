#include "Graph.h"
#include <iostream>



int main() {
    Graph graph("10k.txt");
    graph.text();
    graph.BFS(0);
    std::cout << std::endl;
    std::cout << graph.weg(0, 7738) << std::endl;
    return 0;
}