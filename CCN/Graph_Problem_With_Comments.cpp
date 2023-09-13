#include<bits/stdc++.h> // Includes all the standard C++ libraries

using namespace std;

// Define a constant for infinity
const int INF = numeric_limits<int>::max(); 

/*
Define a function that takes a graph, a source node and a destination node as parameters 
and returns a vector of the shortest path vector<int> distances(graph.size(), INF); 
Initialize a vector of distances from the source to each node with infinity vector<int> previous(graph.size(), -1);
Initialize a vector of previous nodes in the shortest path with -1 
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 
Define a priority queue of pairs of distance and node, ordered by the smallest distance 
*/
vector<int> dijkstra(const vector<vector<pair<int, int>>>& graph, int source, int destination) { 

distances[source] = 0;

// Push the pair of zero and source to the priority queue
pq.push(make_pair(0, source)); 

while (!pq.empty()) { 
    int u = pq.top().second; // Get the node with the smallest distance from the priority queue
    pq.pop(); 

    if (u == destination) { 
        break;
    }

    for (auto& neighbor : graph[u]) { // For each neighbor of the node
        int v = neighbor.first; // Get the neighbor node
        int weight = neighbor.second; // Get the weight of the edge
        
         // If the distance to the neighbor is larger than the distance to the current node plus the weight of the edge
        if (distances[v] > distances[u] + weight) {
        	// Update the distance to the neighbor
            distances[v] = distances[u] + weight; 
            // Update the previous node in the shortest path
            previous[v] = u; 
            pq.push(make_pair(distances[v], v)); // Push the pair of distance and neighbor to the priority queue
        }
    }
}

vector<int> path; 
// Traverse from the destination to the source using the previous vector
for (int v = destination; v != -1; v = previous[v]) { 
    path.push_back(v); 
}
reverse(path.begin(), path.end());

return path; 

}

int main() {  

vector<int> path = dijkstra(graph, 0, 4); 

cout << "Shortest path from 0 to 4: "; 
for (auto& node : path) { 
    cout << node << " ";
}

}