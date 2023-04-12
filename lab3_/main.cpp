#include <iostream>
#include "Graph.h"

int main() {
//    Graph g("../100k.txt");
    Graph g("../g1.txt");
//    g.BFS(1);
    cout << g.weg_len(0, 3) << endl;
    g.weg(0, 3);
}
