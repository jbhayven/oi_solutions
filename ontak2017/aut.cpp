#include <bits/stdc++.h>
using namespace std;

#define MAX_T 500100

void get_ans(const array<int, MAX_T>& bus_inc, int cnt, int T1, int T2) {
    int buses = 0;
    int result = -1;
    for (int i = 0; i <= T2; i++) {
        buses += bus_inc[i];
        
        if (i < T1) continue;
        if (buses < cnt) continue;
        
        if (result == -1)
            result = i;
        else 
            result = -2;
    }
    
    if (result > 0) cout << "TAK" << " " << result << endl;
    else cout << "NIE" << endl;
}

vector< pair<int, int> > buses_at_freq[MAX_T]; 
array<int, MAX_T> bus_inc;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    /* Load data. */
    int n, T1, T2;
    cin >> n >> T1 >> T2;
    
    int k, l, s, t;
    for (int i = 0; i < n; i++) {
        cin >> k >> l >> s >> t;
        
        /* Translate to periods of presence. */
        buses_at_freq[k].push_back({l - s, l + t}); 
    }
    /* Data loaded. */
    
    /* Changes of bus count. */
    bus_inc.fill(0);
    
    for (int i = 1; i < MAX_T; i++) {
        if (buses_at_freq[i].empty()) continue;
        
        /* Periodic bus count component for frequency = i. */
        map<int, int> buffer;
        
        for (auto bus : buses_at_freq[i]) {
            if (bus.second - bus.first >= i - 1) 
                bus.second = bus.first + i - 1;
            
            bus.first = ((bus.first % i) + i) % i;
            bus.second = ((bus.second % i) + i) % i;
            
            if (bus.first > bus.second) {
                buffer[0]++;
                buffer[i]--;
            } 
               
            buffer[bus.first]++;
            buffer[bus.second + 1]--;
        }
        
        /* Translate small incs to big incs. */
        int cnt = 0;
        int bus_total = buses_at_freq[i].size();
        for (const auto& elem : buffer) {
            int delta = elem.second;
            cnt += delta;
            
            if (cnt >= bus_total - 1) {
                if (cnt - delta < bus_total - 1)
                    delta = cnt;    // mark entering the [n-1; n] range
                // else delta is the real change, too 
            }
            else {
                if (cnt - delta >= bus_total - 1)
                    delta = -(cnt - delta); // mark leaving the [n-1; n] range
                else 
                    delta = 0; // changes do not matter
            }
            
            /* Propagate big incs to the real range */
            if (delta == 0) continue;
            
            for (int k = elem.first; k < MAX_T; k += i) 
                bus_inc[k] += delta;
        }
    }
    
    get_ans(bus_inc, n, T1, T2);
    get_ans(bus_inc, n-1, T1, T2);
    
    return 0;
}
