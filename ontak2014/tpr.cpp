#include <bits/stdc++.h>
using namespace std;

struct Ranger {
    const static int rng_size = 400;
    vector< unordered_map<int, int> >rng_changes;
    vector< pair<int, int> > shifts;
    vector< bool > shifted;
    
    void process_range(int i) {
        unordered_map<int, int> change_temp;
        for (int j = min((int) shifts.size(), (i+1) * rng_size) - 1; j >= i * rng_size; j--) {
            if (!shifted[j]) continue;
            
            int result_first = shifts[j].second;
            int result_second = shifts[j].first;
            
            if (change_temp.count(shifts[j].first) > 0) 
                result_second = change_temp[shifts[j].first];
            
            if (change_temp.count(shifts[j].second) > 0) 
                result_first = change_temp[shifts[j].second];
            
            change_temp[shifts[j].first] = result_first;
            change_temp[shifts[j].second] = result_second;
        }
        rng_changes[i] = change_temp;
    }
    
    void alter(int i) {
        shifted[i] = !shifted[i];
        process_range(i / rng_size);
    }
    
    int get_result(int i) {
        for (auto &r : rng_changes)
            if (r.count(i) > 0)
                i = r[i];
        
        return i;
    }
    
    Ranger (const vector< pair<int, int> > shifts) : 
        rng_changes((shifts.size() - 1) / rng_size + 1),
        shifts(shifts),
        shifted(shifts.size(), true) {
        
        for (size_t i = 0; i < rng_changes.size(); i++)
            process_range(i);
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, m; cin >> n >> m;
    
    vector< pair<int, int> > shifts(m);
    for (auto &p : shifts) 
        cin >> p.first >> p.second;
        
    Ranger r(shifts);
    int d = 0;
    
    int q; cin >> q; while(q--) {
        char c; cin >> c;
        if (c == 'C') {
            int k; cin >> k;
            r.alter(--k);
        } else {
            int k; cin >> k;
            d = r.get_result(1 + (k + d) % n);
            cout << d << endl;
        }
    }
    
    return 0;
}
