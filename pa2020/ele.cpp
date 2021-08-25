#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    
    set<pair<int64_t, int>> cand{{0, -1}}; // first = sum_of_vals, second = skipped_places;
    
    int64_t total_sum = 0;
    int temp_score = n;
    
    for (int i = 0; i < n; i++) {
        int val; cin >> val;
        val = -val;
        
        total_sum += val;
        
        auto prev = cand.lower_bound({total_sum, -1});
        
        if (prev != cand.end()) {
            temp_score = prev->second + 1;
            
            while (prev != cand.begin()) {
                prev--;
                if (prev->second <= temp_score) {
                    cand.erase(prev);
                    prev = cand.lower_bound({total_sum, -1});
                } else {
                    break;
                }
            }
            
            if (prev->first == total_sum) {
                cand.erase(prev);
            }
            
            cand.insert({total_sum, temp_score});
        } else {
            temp_score = n;
        }
    }
    
    cout << (n - 1) - temp_score << endl;
    
    return 0;
}
