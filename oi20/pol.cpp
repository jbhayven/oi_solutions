#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 3e6 + 10;

vector<int> paths[MAX_N];

int p[MAX_N];
int s[MAX_N];
int n;

void ukorzen(int i) {
    s[i] = 1;
    
    for (int j : paths[i]) {
        if (j == p[i]) continue;
        
        p[j] = i;
        ukorzen(j);
        
        s[i] += s[j];
    }
}

int get_centroid(int i) {
    for (int j : paths[i]) {
        if (j == p[i]) continue;
        
        if (s[j] * 2 > n) 
            return get_centroid(j);
    }
    
    return i;
}

int64_t count() {
    int64_t result = 0;
    
    for (int i = 1; i <= n; i++) 
        result += s[i] - 1;
    
    return result;
}

bool can_get[MAX_N];
int64_t solve_knapsack(int c) {
    unordered_map<int, int> nums;
    for (int j : paths[c])
        nums[s[j]]++;
        
    const int limit = (n / 2 + 10);
    can_get[0] = true;
    for (auto &e : nums) {
        for (int i = limit; i >= 0; i--) {
            if (!can_get[i]) continue;
            for (int j = 1, ind; j <= e.second && (ind = i + j * e.first) < limit; j++) {
                if (can_get[ind]) break;
                can_get[ind] = true;
            }
        }
    }
    
    int64_t result = 0;
    for (int i = 0; i < limit; i++) {
        if (!can_get[i]) continue;
        result = max(result, (int64_t)(n-1-i) * i);
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        paths[u].push_back(v);
        paths[v].push_back(u);
    }
    
    ukorzen(1);
    int c = get_centroid(1);
    
    p[c] = 0;
    ukorzen(c);
    
    cout << n-1 << " " << count() + solve_knapsack(c) << endl;
    
    return 0;
}
