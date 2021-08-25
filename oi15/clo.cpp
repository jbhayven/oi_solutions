#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 10;

vector<int> graph[MAX_N];
int result[MAX_N];

void propagate(int i) {
    for (int j : graph[i]) {
        if (result[j]) continue;
        
        result[j] = i;
        propagate(j);
    }
}

bool satisfy(int i, vector<bool> &visited, list<int> &order, int prev = -1) {
    visited[i] = true;
    order.push_back(i);
    
    for (int j : graph[i]) {
        if (j == prev) 
            continue;
        
        if (visited[j]) {            
            while (order.front() != j) 
                order.pop_front();
            
            int prev = i;
            for (int k : order) {
                result[k] = prev;
                prev = k;
            }
            
            for (int k : order) {
                propagate(k);
            }
            
            return true;
        } else if (satisfy(j, visited, order, i)) {
            return true;
        }
    }
    
    order.pop_back();
    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, m; cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    vector<bool> visited(n + 10, false);
    
    for (int i = 1; i <= n; i++) {
        if (result[i]) continue;
        
        list<int> order;
        if (!satisfy(i, visited, order)) {
            cout << "NIE" << endl;
            exit(0);
        }
    }
    
    cout << "TAK" << endl;
    for (int i = 1; i <= n; i++) {
        cout << result[i] << "\n";
    }
}
