#include <bits/stdc++.h>
#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <vector>
using namespace std;

#define V 8 // Number of vertices in the graph

// Function to perform Breadth-First Search to find if there is a path from source to sink
bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[t];
}

int main() {
    // Define the capacity matrix of the graph
    int graph[V][V] = {
        {0, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    // Define source-destination pairs for testing
    vector<pair<int, int>> sourceDestPairs = {
        {0, 7},
        {1, 6},
        {3, 5},
        {0, 5},
        {1, 7}
        // You can add more source-destination pairs here
    };

    // Iterate through each source-destination pair
    for (const auto &pair : sourceDestPairs) {
        int s = pair.first; // Source vertex
        int t = pair.second; // Sink vertex

        int rGraph[V][V]; // Residual graph

        // Initialize residual graph with the same capacities as the original graph
        for (int u = 0; u < V; u++)
            for (int v = 0; v < V; v++)
                rGraph[u][v] = graph[u][v];

        int maxFlow = 0;
        int parent[V];
        vector<vector<int>> paths;

        // Calculate edge-disjoint paths using BFS and augmenting paths
        while (bfs(rGraph, s, t, parent)) {
            vector<int> path;
            int pathFlow = INT_MAX;

            // Find the minimum residual capacity along the path
            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                pathFlow = min(pathFlow, rGraph[u][v]);
            }

            // Update residual capacities of the edges and reverse edges along the path
            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                rGraph[u][v] -= pathFlow;
                rGraph[v][u] += pathFlow;
            }

            maxFlow += pathFlow;

            // Store the path in reverse order
            for (int v = t; v != s; v = parent[v]) {
                path.push_back(v);
            }
            path.push_back(s);
            reverse(path.begin(), path.end());
            paths.push_back(path);
        }

        // Print the number of edge-disjoint paths and each path
        cout << "There can be a maximum of " << paths.size() << " edge-disjoint paths from vertex " << s << " to vertex " << t << "." << endl;
        for (const auto &p : paths) {
            cout << "Path: ";
            for (int vertex : p) {
                cout << vertex << " -> ";
            }
            cout << endl;
        }
        cout << endl;
    }

    cout << "****************  End  ******************" << endl;

    return 0;
}
