#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

vector<vector<pii>> graph;

vector<int> dijkstra(int start) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int cost = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (cost > dist[node]) {
            continue;
        }

        for (pii edge : graph[node]) {
            int neighbor = edge.first;
            int weight = edge.second;
            if (cost + weight < dist[neighbor]) {
                dist[neighbor] = cost + weight;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }

    return dist;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    graph.resize(n);

    for (int i = 0; i < m; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        graph[x - 1].push_back({y - 1, w});
        graph[y - 1].push_back({x - 1, w});
    }

    vector<vector<int>> dist(n);
    for (int i = 0; i < n; ++i) {
        dist[i] = dijkstra(i);
    }

    vector<int> shortest_paths;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            shortest_paths.push_back(dist[i][j]);
        }
    }

    sort(shortest_paths.begin(), shortest_paths.end());

    cout << shortest_paths[k - 1] << endl;

    return 0;
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