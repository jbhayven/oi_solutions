#include <bits/stdc++.h>
using namespace std;

bool solve() {
    int n;
    cin >> n;
    
    int prev = 0;
    int curr;
    int odd_xor = 0;
    
    for (int i = 0; i < n; i++, prev = curr) {
        cin >> curr;
        
        if ((n - i) % 2) odd_xor ^= (curr - prev);
    }
    
    return odd_xor;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int u; cin >> u; while(u--) {
        cout << (solve() ? "TAK" : "NIE") << endl;
    }
    
    return 0;
}
