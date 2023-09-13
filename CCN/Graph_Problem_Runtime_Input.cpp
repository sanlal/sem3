#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Structure to represent a graph edge
struct Edge {
    int to;
    int weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

// Function to find the shortest path using Dijkstra's algorithm
void shortestPath(const vector<vector<Edge>>& graph, int source, int destination) {
    int n = graph.size();
    vector<int> distance(n, numeric_limits<int>::max());
    vector<int> parent(n, -1);
    
    distance[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;
            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    
    if (distance[destination] == numeric_limits<int>::max()) {
        cout << "No path from source to destination.\n";
    } else {
        cout << "Shortest path length: " << distance[destination] << endl;
        cout << "Shortest path: ";
        vector<int> path;
        int current = destination;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        for (int i = path.size() - 1; i >= 0; --i) {
            cout << path[i] << " ";
        }
        cout << endl;
    }
}

// Function to detect cycles using DFS
bool hasCycleDFS(const vector<vector<Edge>>& graph, int node, vector<bool>& visited, vector<bool>& recStack) {
    if (!visited[node]) {
        visited[node] = true;
        recStack[node] = true;
        
        for (const Edge& edge : graph[node]) {
            int neighbor = edge.to;
            if (!visited[neighbor] && hasCycleDFS(graph, neighbor, visited, recStack)) {
                return true;
            } else if (recStack[neighbor]) {
                return true;
            }
        }
    }
    recStack[node] = false;
    return false;
}

// Function to count the number of cycles in the graph
int countCycles(const vector<vector<Edge>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);
    int cycleCount = 0;
    
    for (int i = 0; i < n; ++i) {
        if (!visited[i] && hasCycleDFS(graph, i, visited, recStack)) {
            cycleCount++;
        }
    }
    
    return cycleCount;
}

int main() {
    int n, m; // n = number of nodes, m = number of edges
    cout<<"Enter n nodes and m edges:  ";
    cin >> n >> m;
    
    vector<vector<Edge>> graph(n);
    cout<<"Enter Edge from node u to node v with weight w:  ";
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w; // Edge from node u to node v with weight w
        graph[u].emplace_back(v, w);
    }
    
    
    int cycleCount = countCycles(graph);
    cout << "Number of cycles: " << cycleCount << endl;
    
    
    int source, destination;
    cout<<"Enter source and destination:  ";
    cin >> source >> destination;
     
    shortestPath(graph, source, destination);
    
    
    
    return 0;
}