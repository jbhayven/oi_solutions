#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; 
    cin >> n;
    
    vector<int> klo(n);
    for (int &i : klo) cin >> i;
    
    vector<pair<int, int>> klo_ptr(n);
    for (int i = 0; i < n; i++)
        klo_ptr[i] = {(i + 1) - klo[i], i};
    
    sort(klo_ptr.begin(), klo_ptr.end());
    
    /* first : height
     * second: value 
     * invariant : a.ST < b.ST => a.ND < b.ND
     */
    set< pair<int, int> > partial{ {0, 0}, {n + 2, n + 2} };
    
    /* For result retrieval */
    vector<int> next_klo(n);
    vector<int> last_at_h(n + 2, -1);
    
    for (pair<int, int> ptr : klo_ptr) {
        if (ptr.first < 0) continue;
        
        int h = klo[ptr.second];
        
        auto best_below = --partial.lower_bound({h, -1});
        
        next_klo[ptr.second] = last_at_h[best_below->first];
        
        pair<int, int> new_pair = { h, best_below->second + 1 };
        
        while (partial.lower_bound(new_pair)->second <= new_pair.second)
            partial.erase(partial.lower_bound(new_pair));
        
        partial.insert(new_pair);
        last_at_h[h] = ptr.second;
    }
    
    /* Find which blocks need to be removed to achieve the optimal solution. */
    partial.erase({0, 0});
    partial.erase({n+2, n+2});
    
    if (partial.empty()) {
        cout << 0 << endl;
        return 0;
    }
    
    stack<int> to_put;
    int last = last_at_h[(--partial.end())->first];
    while (last != -1) {
        to_put.push(last);
        last = next_klo[last];
    }
    
    vector<int> to_remove;
    int removed = 0;
    for (int i = 0; i < n; i++) {
        if (to_put.empty()) break;
        
        if (i == to_put.top()) {
            to_put.pop();
        } else {
            if (to_put.top() + 1 - klo[to_put.top()] > removed) {
                removed++;
                to_remove.push_back(i);
            }
        }
    }
    
    cout << to_remove.size() << endl;
    for (int i : to_remove) cout << i + 1 << " ";
    cout << endl;
    
    return 0;
}
