#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    Graph g("../Land.txt");
    g.printHamiltonKreis("Suceava");
}
