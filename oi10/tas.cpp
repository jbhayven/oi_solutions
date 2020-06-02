#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, l;
    cin >> n >> l;
    
    vector<int> perm(n);
    for(int &n : perm) {
        cin >> n;
        --n;
    }
    
    vector<bool> processed(n, false);
    vector<vector<int> > cycles_by_len(n+1);
    
    for(int i = 0; i < n; i++) {
        if(!processed[i]) {
            int len, pos;
            
            /* Get cycle len */
            len = 0;
            pos = i;
            do {
                len++;
                processed[pos] = true;
                pos = perm[pos];
            } while(pos != i);
                
            // save only the starting point to save memory
            cycles_by_len[len].push_back(i); 
        }
    }
    
    /* Combine partial cycles */
    vector<int> orig(n);
    
    for(int len = 1; len <= n; len++) {
        if(cycles_by_len[len].empty()) continue;
        
        int mixed = 1;
        
        while(gcd(len * mixed, l) != mixed) 
            mixed++; // I can't think of a better solution ATM but this amortises, so it's fine
        
        while(!cycles_by_len[len].empty()) {
            vector<int> real_cycle(mixed * len);
            
            for(int off = 0; off < mixed; off++) {
                size_t pos = cycles_by_len[len].back();
                cycles_by_len[len].pop_back();
                
                size_t new_pos = pos, real_pos = off;
                do {
                    real_cycle[real_pos] = new_pos;
                    new_pos = perm[new_pos];
                    real_pos = (real_pos + l) % real_cycle.size();
                } while(new_pos != pos);
            }
            
            for(size_t i = 0; i < real_cycle.size(); i++)
                orig[real_cycle[i]] = real_cycle[(i + 1) % real_cycle.size()];
        }
    }
    
    for(int i = 0; i < n; i++)
        cout << orig[i] + 1 << '\n';

    return 0;
}
