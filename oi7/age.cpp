#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 251;

struct config {
    int mode;
    int a, b;
};

int visited[2][MAX_N][MAX_N];
vector<int> graph[MAX_N];

void try_move(queue<config> &q, int a, int b, int dist, int mode) {
    if(visited[!mode][a][b] == 0) {
        visited[!mode][a][b] = dist + 1;
        q.push(config{
            .mode = !mode,
            .a = a, .b = b
        });
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    int a, b;
    cin >> a >> b;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
    
    visited[0][a][b] = 1;
    queue<config> q{{config{ .mode = 0, 
                             .a = a,
                             .b = b }}};
    
    while (!q.empty()) {
        config top = q.front();
        q.pop();
        
        int dist = visited[top.mode][top.a][top.b];
        
        if(top.mode == 0) 
            for(int v : graph[top.a])
                try_move(q, v, top.b, dist, 0);
        else 
            for(int v : graph[top.b])
                try_move(q, top.a, v, dist, 1);
    }
    
    int result = INT_MAX;
    for (int i = 1; i <= n; i++)
        if(visited[0][i][i] > 0)
            result = min(result, visited[0][i][i]);
    
    if (result == INT_MAX) 
        cout << "NIE" << endl;
    else 
        cout << result / 2 << endl;
        
    return 0;
}
