#include "Graph.h"
#include <queue>
#include <stack>

Graph::Graph() = default;


Graph::Graph(const string &filename) {
    ifstream file(filename);
    file >> vertices >> edges;
    adj_list.resize(vertices);
    int source, destination;
    while (file >> source >> destination) {
        adj_list[source].push_back(destination);
        adj_list[destination].push_back(source);
    }
}

Graph::Graph(vector<vector<int>> &adjacency_list, int edges, int vertices) {
    this->adj_list = adjacency_list;
    this->vertices = vertices;
    this->edges = edges;
}

Graph Graph::makeFromMatrix(vector<vector<int>> &adjacency_matrix, int edges, int vertices) {
    Graph new_graph{};
    new_graph.adj_matrix = adjacency_matrix;
    new_graph.edges = edges;
    new_graph.vertices = vertices;

    return new_graph;
}

Graph Graph::makeFromEdgeList(vector<pair<int, int>> &edge_list, int edges, int vertices) {
    Graph new_graph{};
    new_graph.edge_list = edge_list;
    new_graph.edges = edges;
    new_graph.vertices = vertices;
    return new_graph;
}

void Graph::readEdgeList(const string &file) {
    ifstream f;
    f.open(file);
    f >> vertices;
    f >> edges;

    for (int i = 0; i < edges; i++) {
        pair<int, int> tmp{};
        f >> tmp.first;
        f >> tmp.second;

        edge_list.push_back(tmp);
    }
}

void Graph::printEdgeList() const {
    for (const auto &edge: edge_list)
        cout << edge.first << ' ' << edge.second << '\n';
}

void Graph::printNeighbouringVerticesEL(int _v) const {
    for (const auto &edge: edge_list) {
        if (edge.first == _v)
            cout << edge.second << ' ';
        else if (edge.second == _v)
            cout << edge.first << ' ';
    }
}

bool Graph::isEdgeInGraphEL(const pair<int, int> &edge) const {
    return std::any_of(edge_list.begin(), edge_list.end(),
                       [edge](auto e) { return e == edge; });
}

bool Graph::isVertexInGraphEL(int _v) const {
    return std::any_of(edge_list.begin(), edge_list.end(),
                       [_v](auto e) { return e.first == _v || e.second == _v; });
}

void Graph::BFS(int s) const {
    //initialize visited with 0
    vector<bool> visited(vertices, false);
    queue<int> q;

    //mark root as visited and add it to queue
    visited[s] = true;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";
        for (int vertex: adj_list[u]) {
            if (!visited[vertex]) {
                visited[vertex] = true;
                q.push(vertex);
            }
        }
    }
}

void Graph::DFS(int s) const {
    //initialize visited with 0
    vector<bool> visited(vertices, false);
    stack<int> st;

    //mark root as visited and add it to stack
    visited[s] = true;
    st.push(s);

    while (!st.empty()) {
        int u = st.top();
        st.pop();
        cout << u << " ";
        for (int vertex: adj_list[u]) {
            if (!visited[vertex]) {
                visited[vertex] = true;
                st.push(vertex);
            }
        }
    }
}

void Graph::BFS_AM(int s) const {
    //initialise visited with 0
    vector<bool> visited(vertices, false);
    queue<int> q;

    // mark root as visited and add it to queue
    visited[s] = true;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";
        for (int v = 0; v < vertices; v++) {
            if (adj_matrix[u][v] && !visited[v]) { // check if v is adjacent to u and not visited before
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

void Graph::DFS_AM(int s) const {
    //initialise visited with 0
    vector<bool> visited(adj_matrix.size(), false);

    //add root to stack
    stack<int> stack;
    stack.push(s);

    while (!stack.empty()) {
        int vertex = stack.top();
        stack.pop();

        if (!visited[vertex]) {
            visited[vertex] = true;
            cout << vertex << " ";

            for (int v = int(adj_matrix.size()) - 1; v >= 0; v--) {
                if (adj_matrix[vertex][v] && !visited[v]) {
                    stack.push(v);
                }
            }
        }
    }
}

int Graph::weg_len(int start, int stop) const {
    std::vector<bool> visited(vertices, false);
    std::vector<int> length(vertices, INT16_MAX);
    std::deque<int> q;
    q.push_back(start);
    visited[start] = true;
    length[start] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop_front();

        if (current == stop)
            return length[current];

        for (auto neighbor: adj_list[current]) {
            if (!visited[neighbor]) {
                q.push_back(neighbor);
                length[neighbor] = length[current] + 1;
                visited[neighbor] = true;
            }
        }
    }
    std::cout << std::endl;

    std::cout << "No path from " << start << " to " << stop << "\n";
    return -1;
}

void Graph::weg(int start, int stop) const {
    std::vector<bool> visited(vertices, false);
    std::vector<int> parent(vertices, -1);
    std::deque<int> q;
    q.push_back(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop_front();

        if (current == stop) {
            // Backtrack to find the shortest path
            std::vector<int> path;
            path.push_back(current);
            int node = current;
            while (parent[node] != -1) {
                path.push_back(parent[node]);
                node = parent[node];
            }
            std::cout << "Shortest path from " << start << " to " << stop << ": ";
            for (int i = int(path.size()) - 1; i >= 0; i--)
                std::cout << path[i] << " ";
            std::cout << std::endl;
            return;
        }

        for (int neighbor: adj_list[current]) {
            if (!visited[neighbor]) {
                q.push_back(neighbor);
                visited[neighbor] = true;
                parent[neighbor] = current;
            }
        }
    }

    // If we reach here, there is no path from start to stop
    std::cout << "No path from " << start << " to " << stop << std::endl;
}