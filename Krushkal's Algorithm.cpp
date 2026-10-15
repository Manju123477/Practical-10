#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) const {
        return weight < other.weight;
    }
};

int find_set(int v, vector<int>& parent) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v], parent);
}

void union_sets(int a, int b, vector<int>& parent, vector<int>& rank) {
    a = find_set(a, parent);
    b = find_set(b, parent);
    if (a != b) {
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

int main() {
    int vertices = 9;
    vector<Edge> edges = {
        {0, 1, 4},
        {0, 7, 8},
        {1, 2, 8},
        {1, 7, 11},
        {2, 3, 7},
        {2, 8, 2},
        {2, 5, 4},
        {3, 4, 9},
        {3, 5, 14},
        {4, 5, 10},
        {5, 6, 2},
        {6, 7, 1},
        {6, 8, 6},
        {7, 8, 7}
    };

    int mst_cost = 0;
    vector<int> parent(vertices);
    vector<int> rank(vertices, 0);
    
    for (int i = 0; i < vertices; i++) {
        parent[i] = i;
    }

    sort(edges.begin(), edges.end());

    vector<Edge> mst_edges;
    
    for (Edge e : edges) {
        if (find_set(e.u, parent) != find_set(e.v, parent)) {
            mst_cost += e.weight;
            mst_edges.push_back(e);
            union_sets(e.u, e.v, parent, rank);
        }
    }

    cout << "Total Cost: " << mst_cost << "\n";
    for (Edge e : mst_edges) {
        cout << e.u << " - " << e.v << " : " << e.weight << "\n";
    }

    return 0;
}
