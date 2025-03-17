#include "dijkstras.h"
#include <algorithm>
#include <stack>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distances(G.numVertices, INF);
    vector<bool> visited(G.numVertices, false);
    distances[source] = 0;
    previous.resize(G.numVertices, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    previous[source] = -1;
    pq.push({0, source});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;

        visited[u] = true;
        for (const Edge& e : G[u]) {
            int v = e.dst;
            int wt = e.weight;
            if (distances[u] + wt < distances[v]) {
                previous[v] = u;
                distances[v] = distances[u] + wt;
                pq.push(pair{distances[v], v});
            }
        }
    }

    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    stack<int> res_stack;

    for (size_t curr = destination; curr != -1; curr = previous[curr]) {
        res_stack.push(curr);
    }
    
    while(!res_stack.empty()){
        path.push_back(res_stack.top());
        res_stack.pop();
    }
    return path;
}

void print_path(const vector<int>& path, int total) {
    for (int i : path) {
        cout << i << " ";
    }
    cout << endl << "Total cost is " << total << endl;
}