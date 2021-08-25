#include <bits/stdc++.h>
using namespace std;

bool check(vector<pair<int, int>> &events) {
    int64_t last_pos = 0;
    int64_t reservoir = 0;
    int64_t curr_flow = 0;
    
    for (auto ev : events) {
        reservoir += curr_flow * (ev.first - last_pos);
        if (reservoir < 0) 
            return false;
        
        last_pos = ev.first;
        curr_flow += ev.second;
    }
    
    return true;
}

bool solve() {
    int n; cin >> n;
    
    vector<pair<int, int>> events;
    
    for (int i = 0; i < n; i++) {
        int l, a, b;
        cin >> l >> a >> b;
        
        events.push_back({a, l});
        events.push_back({b, -l});
    }
    
    sort(events.begin(), events.end());

    if (!check(events)) return false;
    
    reverse(events.begin(), events.end());
    for (auto &ev : events)
        ev.second = -ev.second;
        
    if (!check(events)) return false;
    
    return true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int t; cin >> t; while(t--) {
        cout << (solve() ? "TAK" : "NIE") << endl;
    }
    
    return 0;
}
