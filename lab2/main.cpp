#include <iostream>
#include "Graph.h"
using namespace std;

int main() {
    Graph g1{};
    g1.leseDateiZuGraph("../kanten.in");
    g1.zeigeKantenListe();
    g1.zeigeAngrenzendeKnoten(1);


//    Graph g1, g2;
//    g1.leseDateiZuGraph("../graph1.in");
//    g2.leseDateiZuGraph("../graph2.in");
//
//    Graph res = Graph::vereinigungVonGraphen(g1, g2);
//    res.zeigeKantenListe();
}
