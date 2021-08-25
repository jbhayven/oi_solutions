#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    
    vector<uint64_t> w(n);
    for (auto &i : w) cin >> i;
    
    set<uint64_t> fish(w.begin(), w.end());
    
    int q; cin >> q;
    while (q--) {
        int num; cin >> num;
        
        switch(num) {
        case 1:
            uint64_t s, k;
            cin >> s >> k;
            
            vector<uint64_t> deleted;
            
            int steps = 0;
            while (s < k) {
                auto it = fish.upper_bound(s);
                if (it == fish.begin()) {
                    steps = -1;
                    break;
                }
                
                it--;
                steps++;
                s += *it;
                deleted.push_back(it);
                fish.remove(it);
            }
        }
    }
    
    return 0;
}
