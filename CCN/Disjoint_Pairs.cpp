//C++ program to find maximum number of edge disjoint paths

#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
using namespace std;

#define V 8 // Number of vertices in the graph

// Function to perform Breadth-First Search to find if there is a path from source to sink
bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
	bool visited[V];
	memset(visited, 0, sizeof(visited));

	queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		for (int v = 0; v < V; v++)
		{
			if (visited[v] == false && rGraph[u][v] > 0)
			{
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	return (visited[t] == true); // Return true if there's a path from source to sink
}

// Function to find the maximum number of edge-disjoint paths
int findDisjointPaths(int graph[V][V], int s, int t)
{
	int u, v;
	int rGraph[V][V]; // Residual graph to keep track of remaining capacities

	// Initialize residual graph with the same capacities as the original graph
	for (u = 0; u < V; u++)
		for (v = 0; v < V; v++)
			rGraph[u][v] = graph[u][v];

	int parent[V];
	int max_flow = 0;

	while (bfs(rGraph, s, t, parent)) // While there's a path from source to sink
	{
		int path_flow = INT_MAX; // Initialize the flow of the path

		// Find the minimum residual capacity along the path
		for (v = t; v != s; v = parent[v])
		{
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}

		// Update residual capacities of the edges and reverse edges along the path
		for (v = t; v != s; v = parent[v])
		{
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}

		max_flow += path_flow; // Add the flow of this path to the overall flow
	}

	return max_flow; // Return the maximum number of edge-disjoint paths
}

int main()
{
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

	cout << "There can be a maximum of " << findDisjointPaths(graph, s, t)
		<< " edge-disjoint paths from vertex " << s << " to vertex " << t << "." << endl;

	return 0;
}




/*

Enter the adjacency matrix of the graph:
0 1 1 1 0 0 0 0
0 0 1 0 0 0 0 0
0 0 0 1 0 0 1 0
0 0 0 0 0 0 1 0
0 0 1 0 0 0 0 1
0 1 0 0 0 0 0 1
0 0 0 0 0 1 0 1
0 0 0 0 0 0 0 0
Enter the source vertex (0-7): 0
Enter the sink vertex (0-7): 7
There can be a maximum of 2 edge-disjoint paths from vertex 0 to vertex 7.


*/