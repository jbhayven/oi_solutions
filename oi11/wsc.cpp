#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1010000;

int n, w, z;
int par[MAX_N];
int wsc[MAX_N];
int zac[MAX_N];
int dist[MAX_N];
vector<int> kraw[MAX_N];

void ukorzen(int i) {
    /* Avoid recursion – causes memory limit overflow */
    vector<int> to_root{i};
    par[i] = 0;
    dist[0] = -1;
    
    for (size_t j = 0; j < to_root.size(); j++) {
        i = to_root[j];
        
        wsc[i] = zac[i] = 0;
        dist[i] = dist[par[i]] + 1;
        
        if (i <= w) wsc[i]++;
        if (i >= n - z + 1) zac[i]++;
        
        for (int v : kraw[i]) {
            if (v == par[i]) continue;
            
            par[v] = i;
            to_root.push_back(v);
        }
    }
    
    for (auto it = to_root.rbegin(); it != to_root.rend(); it++) {
        wsc[par[*it]] += wsc[*it];
        zac[par[*it]] += zac[*it];
    }
}

int znajdz_most(int i) {
    while (wsc[i] != 0) {
        for (int v : kraw[i]) {
            if (v != par[i] && zac[v] == z)  {
                i = v;
                break;
            }
        }
    }
    
    return i;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n >> w >> z;
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        kraw[a].push_back(b);
        kraw[b].push_back(a);
    }
    
    ukorzen(1);
    ukorzen(znajdz_most(1));
    
    vector<int> train_dists(2 * MAX_N, 0);
    vector<int> west_dists(MAX_N, 0);
    
    int p; cin >> p;
    for (int i = 0; i < p; i++) {
        int poc; cin >> poc;
        train_dists[dist[poc]]++;
    }
        
    for (int i = n - z + 1; i <= n; i++)
        west_dists[dist[i]]++;
        
    int result = 0;
    int train_cnt = 0;
    int i;
    
    /* Handle delays */
    for (i = 0; train_cnt < p; i++) {
        if (train_dists[i] == 0) continue;
        
        train_cnt++;
        train_dists[i + 1] += train_dists[i] - 1;
        train_dists[i] = 1;
    }
    
    /* Trains that set out last will be directed to the closest crossings */
    int j = 0;
    for (; i >= 0; i--) {
        if (train_dists[i] == 0) continue;
        
        while (west_dists[j] == 0)
            j++;
        
        west_dists[j]--;
        result = max(result, i + j);
    }
    
    cout << result << endl;
    
    return 0;
}
