#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; int64_t m;
    cin >> n >> m;
    
    int64_t result = 0;
    int64_t pref_sum = 0;
    set<int64_t> sums({0, m});
    
    for (int i = 1; i <= n; i++) {
        int64_t a_i;
        cin >> a_i;
        
        pref_sum = ((pref_sum + a_i) % m + m) % m;
        result = max(result, m - (*sums.upper_bound(pref_sum) - pref_sum));
        
        sums.insert(pref_sum);
        sums.insert(pref_sum + m);
    }
    
    cout << result << endl;
    
    return 0;
}
