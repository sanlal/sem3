//#include<bits/stdc++.h>

#include<bits/stdc++.h>
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
    int graph[V][V]; // Adjacency matrix for the graph

    cout << "Enter the adjacency matrix of the graph:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
        }
    }

    int s, t;
    cout << "Enter the source vertex (0-" << V - 1 << "): ";
    cin >> s;
    cout << "Enter the sink vertex (0-" << V - 1 << "): ";
    cin >> t;

    if (s < 0 || t < 0 || s >= V || t >= V) {
        cout << "Invalid source or sink vertex." << endl;
        return 1;
    }

    int rGraph[V][V]; // Residual graph to keep track of remaining capacities

    // Initialize residual graph with the same capacities as the original graph
    for (int u = 0; u < V; u++)
        for (int v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int maxFlow = 0;
    int parent[V];

    vector<vector<int>> paths;

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

    cout << "There can be a maximum of " << paths.size() << " edge-disjoint paths from vertex " << s << " to vertex " << t << "." << endl;

    // Print the paths
    for (const auto &p : paths) {
        cout << "Path: ";
        for (int vertex : p) {
            cout << vertex << " -> ";
        }
        cout << "End" << endl;
    }

    return 0;
}






//#include <iostream>
//#include <limits.h>
//#include <string.h>
//#include <queue>
//#include <vector>
//using namespace std;
//
//#define V 8 // Number of vertices in the graph
//
//// Function to perform Breadth-First Search to find if there is a path from source to sink
//bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
//    bool visited[V];
//    memset(visited, 0, sizeof(visited));
//
//    queue<int> q;
//    q.push(s);
//    visited[s] = true;
//    parent[s] = -1;
//
//    while (!q.empty()) {
//        int u = q.front();
//        q.pop();
//
//        for (int v = 0; v < V; v++) {
//            if (!visited[v] && rGraph[u][v] > 0) {
//                q.push(v);
//                parent[v] = u;
//                visited[v] = true;
//            }
//        }
//    }
//
//    return visited[t];
//}
//
//int main() {
//    int graph[V][V]; // Adjacency matrix for the graph
//
//    cout << "Enter the adjacency matrix of the graph:" << endl;
//    for (int i = 0; i < V; i++) {
//        for (int j = 0; j < V; j++) {
//            cin >> graph[i][j];
//        }
//    }
//
//    int s, t;
//    cout << "Enter the source vertex (0-" << V - 1 << "): ";
//    cin >> s;
//    cout << "Enter the sink vertex (0-" << V - 1 << "): ";
//    cin >> t;
//
//    if (s < 0 || t < 0 || s >= V || t >= V) {
//        cout << "Invalid source or sink vertex." << endl;
//        return 1;
//    }
//
//    int rGraph[V][V]; // Residual graph to keep track of remaining capacities
//
//    // Initialize residual graph with the same capacities as the original graph
//    for (int u = 0; u < V; u++)
//        for (int v = 0; v < V; v++)
//            rGraph[u][v] = graph[u][v];
//
//    int maxFlow = 0;
//    int parent[V];
//
//    vector<vector<int>> paths;
//
//    while (bfs(rGraph, s, t, parent)) {
//        vector<int> path;
//        int pathFlow = INT_MAX;
//
//        // Find the minimum residual capacity along the path
//        for (int v = t; v != s; v = parent[v]) {
//            int u = parent[v];
//            pathFlow = min(pathFlow, rGraph[u][v]);
//        }
//
//        // Update residual capacities of the edges and reverse edges along the path
//        for (int v = t; v != s; v = parent[v]) {
//            int u = parent[v];
//            rGraph[u][v] -= pathFlow;
//            rGraph[v][u] += pathFlow;
//        }
//
//        maxFlow += pathFlow;
//
//        // Store the path in reverse order
//        for (int v = t; v != s; v = parent[v]) {
//            path.push_back(v);
//        }
//        path.push_back(s);
//        reverse(path.begin(), path.end());
//        paths.push_back(path);
//    }
//
//    cout << "There can be a maximum of " << paths.size() << " edge-disjoint paths from vertex " << s << " to vertex " << t << "." << endl;
//
//    // Print the paths
//    for (const auto &p : paths) {
//        cout << "Path: ";
//        for (int vertex : p) {
//            cout << vertex << " -> ";
//        }
//        cout << "End" << endl;
//    }
//
//    return 0;
//}
