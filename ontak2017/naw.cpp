#include <bits/stdc++.h>
using namespace std;

const unordered_map<char, int> mappings = {
    {'(', 0},
    {')', 1},
    {'[', 2},
    {']', 3},
    {'{', 4},
    {'}', 5},
    {'<', 6},
    {'>', 7}
};

const int MAX_N = 210;

long long shortest[MAX_N][MAX_N];
bool handled[MAX_N][MAX_N];

vector<int> where_to[MAX_N][8];

int n, m, s, t;

struct from_shortest {
    bool operator()(pair<int, int> a, pair<int, int> b) const {
        return shortest[a.first][a.second] > shortest[b.first][b.second];
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n >> m >> s >> t;
    
    for (int i = 0; i < m; i++) {
        int a, b;
        char c; 
        cin >> a >> b >> c;
        if (mappings.at(c) % 2 == 0) 
            where_to[b][mappings.at(c)].push_back(a);
        else 
            where_to[a][mappings.at(c)].push_back(b);
    }
    
    using PI = pair<int, int>;
    priority_queue<PI, vector<PI>, from_shortest> cand;
    
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if (i != j)
                shortest[i][j] = 1e18;
            else
                cand.push(make_pair(i, j));
                
    while(!cand.empty()) {
        PI top = cand.top(); cand.pop();
        int u = top.first, v = top.second;
        if (handled[u][v]) continue;
        
        handled[u][v] = true;
        
        // handle all expansions
        for (int i = 0; i < 4; i++) 
            for (int prev : where_to[u][2 * i])
                for (int next : where_to[v][2 * i + 1])
                    if (shortest[prev][next] > shortest[u][v] + 2) {
                        shortest[prev][next] = shortest[u][v] + 2;
                        cand.push(make_pair(prev, next));
                    }
        
        // handle all concatenations
        for (int z = 1; z <= n; z++) {
            if (shortest[u][z] > shortest[u][v] + shortest[v][z]) {
                shortest[u][z] = shortest[u][v] + shortest[v][z];
                cand.push(make_pair(u, z));
            }
            
            if (shortest[z][v] > shortest[z][u] + shortest[u][v]) {
                shortest[z][v] = shortest[z][u] + shortest[u][v];
                cand.push(make_pair(z, v));
            }
        }
    }
    
    if (shortest[s][t] == 1e18) 
        cout << -1 << endl;
    else
        cout << shortest[s][t] << endl;
    
    return 0;
}
