#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

// A vector of vectors of pairs to represent the graph's adjacency list
vector<vector<pii>> graph;

// Function to perform Dijkstra's algorithm and return the shortest distances from the start node
vector<int> dijkstra(int start) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX); // Initialize all distances to infinity
    dist[start] = 0; // Distance to the start node is set to 0
    priority_queue<pii, vector<pii>, greater<pii>> pq; // Min-heap priority queue
    pq.push({0, start}); // Push the start node with distance 0

    // Dijkstra's algorithm loop
    while (!pq.empty()) {
        int cost = pq.top().first; // Current cost to reach this node
        int node = pq.top().second; // Current node
        pq.pop(); // Remove the node from the queue

        // Skip if this node has been visited with a shorter path
        if (cost > dist[node]) {
            continue;
        }

        // Explore neighbors of the current node
        for (pii edge : graph[node]) {
            int neighbor = edge.first; // Neighbor node
            int weight = edge.second; // Weight of the edge to the neighbor
            // Update distance and push to queue if a shorter path is found
            if (cost + weight < dist[neighbor]) {
                dist[neighbor] = cost + weight;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }

    return dist; // Return the array of shortest distances
}

int main() {
    int n, m, k;
    cin >> n >> m >> k; // Input the number of nodes, edges, and kth element

    graph.resize(n); // Resize the graph vector to have 'n' nodes

    // Input the edges and their weights
    for (int i = 0; i < m; ++i) {
        int x, y, w; // Source node, destination node, edge weight
        cin >> x >> y >> w;
        graph[x - 1].push_back({y - 1, w}); // Add edge to adjacency list
        graph[y - 1].push_back({x - 1, w}); // Add edge (graph is undirected)
    }

    vector<vector<int>> dist(n); // 2D vector to store shortest distances from all nodes
    for (int i = 0; i < n; ++i) {
        dist[i] = dijkstra(i); // Run Dijkstra's algorithm for each node
    }

    vector<int> shortest_paths; // Vector to store all shortest paths
    // Generate all shortest path lengths between pairs of nodes
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            shortest_paths.push_back(dist[i][j]); // Add shortest path length to vector
        }
    }

    sort(shortest_paths.begin(), shortest_paths.end()); // Sort the vector of shortest paths

    cout << shortest_paths[k - 1] << endl; // Output the kth shortest path

    return 0; // Return 0 to indicate successful completion
}



/*
6 10 5
2 5 1
5 3 9
6 2 2
1 3 1
5 1 8
6 5 10
1 6 5
6 4 6
3 6 2
3 4 5
output: 3

7 15 18
2 6 3
5 7 4
6 5 4
3 6 9
6 7 7
1 6 4
7 1 6
7 2 1
4 3 2
3 2 8
5 3 6
2 5 5
3 7 9
4 1 8
2 1 1
output: 9
*/