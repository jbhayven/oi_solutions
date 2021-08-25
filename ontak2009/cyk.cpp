#include <bits/stdc++.h>
using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;

int go(int i, VVI &graph, VI &color, int c = 1, int p = -1) {
    color[i] = c;
    
    for (int j : graph[i]) {
        if (j == p) continue;
        
        if (color[j] == 0) {
            int ret = go(j, graph, color, 3 - c, i);
            if (ret == 0) continue;
            
            if (ret > 0) cout << i << " ";
            if (ret == i) {
                ret = -1;
                cout << endl;
            }
            
            return ret;
        } else if (color[j] == color[i]) {
            cout << "TAK " << i << " ";
            return j;
        }
    }
    
    return 0;
}

void solve() {
    int n, m;
    cin >> n >> m;
    
    VVI graph(n + 3);
    VI color(n + 3, 0);
    
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    for (int i = 1; i <= n; i++)
        if (color[i] == 0 && go(i, graph, color) != 0) return;
    
    cout << "NIE" << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int t; cin >> t; while (t--) solve();
    
    return 0;
}
