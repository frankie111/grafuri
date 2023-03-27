#include <vector>

using namespace std;

class Graph {
private:

    int n{};
    int m{};
    int matrix[100][100]{};
    vector<int> list[100]{};
    
public:

    Graph();

    void matrixToList();

    void addEdge(int x, int y);

    bool isEdge(int x, int y);

    void printGraph(bool asMatrix = true);

    int maxOrderMatrix();

    int minOrderMatrix();

    int maxOrderList();

    int minOrderList();
};