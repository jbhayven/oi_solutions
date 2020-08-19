#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    
    vector<int> o(n);
    for (int &i : o) cin >> i;
    
    vector<long long> result(n, 0);
    for (int i = 0; i < n; i++) {
        result[i] = o[i];
        
        long long bonus = 0;
        if (i >= 2) bonus = result[i-2];
        if (i >= 3) bonus = max(bonus, result[i-3] + min(o[i-1], o[i-2]));
        
        result[i] += bonus;
    }
    
    cout << *max_element(result.begin(), result.end()) << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int z; cin >> z; while(z--) {
        solve();
    }
    
    return 0;
}
