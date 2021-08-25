#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 10;

int n, m;
vector<int> edge[MAX_N];
int degree[MAX_N];
bool done[MAX_N];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
        
    cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        edge[a].push_back(b);
        edge[b].push_back(a);
        
        degree[a]++;
        degree[b]++;
    }
    
    set<pair<int, int>> degs;
    
    for (int i = 1; i <= n; i++) 
        degs.emplace(degree[i], i);
    
    int result = 0;
    while (!degs.empty()) {
        auto top = *degs.begin();
        degs.erase(degs.begin());
        
        result = max(result, top.first);
        done[top.second] = true;
        
        for (int i : edge[top.second])
            degs.erase({ degree[i], i });
        
        for (int i : edge[top.second]) 
            degree[i]--;
            
        for (int i : edge[top.second]) if (!done[i]) 
            degs.emplace(degree[i], i);
    }
    
    cout << result << endl;
    
    return 0;
}
