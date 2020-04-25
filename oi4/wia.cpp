#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 3010;

vector<int> graph[MAX_N];
vector<int> anti[MAX_N];

vector<bool> trusted;
vector<bool> visited;

void DFS(int i) {
    visited[i] = true;
    
    for(auto v : graph[i]) {
        if(visited[v] == false)
            DFS(v);
        if(trusted[v] == false)
            trusted[i] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> n >> m;
    
    while(m--) {
        int a, b;
        cin >> a >> b;
        if(b > 0) graph[a].push_back(b);
        else anti[a].push_back(-b);
    }
    
    trusted = vector<bool>(n, true);
    
    for(int i = 1; i <= n; i++) {
        if(trusted[i]) {
            visited = vector<bool>(n, false);
            DFS(i);
         }
        for(int j = 1; trusted[i] && j <= n; j++) {
            if (visited[j] == false) continue;
            for (int v : anti[j]) { 
                if (visited[v]) {
                    trusted[i] = false;
                    break;
                }
            }
        }
        if(trusted[i] == false) 
            cout << i << endl;
    }    
    
    if(accumulate(trusted.begin(), trusted.end(), 
                  true, [](bool a, bool b){ return a && b; } )) 
        cout << "NIKT" << endl;
        
    return 0;
}
