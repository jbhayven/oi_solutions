#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 200100;

vector<int> roads[MAX_N];
bool visited[MAX_N];
char colour[MAX_N];

bool dfs(int i, char c = 'K') {
    colour[i] = c;
    visited[i] = true;
    
    for (int v : roads[i]) {
        if (visited[v]) continue;
        
        if (!dfs(v, c == 'K' ? 'S' : 'K')) {
            return false;
        }
    }
    
    for (int v : roads[i]) {
        if (colour[i] != colour[v]) {
            return true;
        }
    }
    
    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    while(m--) {
        int a, b;
        cin >> a >> b;
        roads[a].push_back(b);
        roads[b].push_back(a);
    }
    
    for (int i = 1; i <= n; i++) {
        if (visited[i]) continue;
        
        if (!dfs(i)) {
            cout << "NIE" << endl;
            return 0;
        }
    }
    
    cout << "TAK" << endl;
    for (int i = 1; i <= n; i++) {
        cout << colour[i] << endl;
    }
    
    return 0;
}
