#ifndef LAB2_GRAPH_H
#define LAB2_GRAPH_H

#include <vector>
#include <string>

using namespace std;

class Graph {
private:
    int n{};
    int m{};
    vector<pair<int, int>> edge_list{};

public:
    Graph();

    explicit Graph(vector<pair<int, int>> &edge_list);

    void leseDateiZuGraph(const string &datei);

    void zeigeKantenListe() const;

    void zeigeAngrenzendeKnoten(int _n) const;

    static Graph vereinigungVonGraphen(Graph &g1, Graph &g2);

    [[nodiscard]] bool isEdgeInGraph(const pair<int, int> &edge) const;

    [[nodiscard]] bool isVertexInGraph(int n) const;
};


#endif //LAB2_GRAPH_H
