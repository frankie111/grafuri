#include "Graph.h"

#include<iostream>
#include<fstream>

using namespace std;

int main() {

    Graph g;
    //cout<<g.isEdge(0,1)<<endl;
    g.printGraph();
    g.matrixToList();
    cout << endl;
    g.printGraph(false);

    cout << endl;
    cout << g.maxOrderMatrix() << ' ';
    cout << g.maxOrderList() << ' ';
    cout << g.minOrderMatrix() << ' ';
    cout << g.minOrderList() << ' ';

}