#include <bits/stdc++.h>
using namespace std;

class DomTree {
    using rec_t = pair<int, int>;
    vector<rec_t> vals;
    size_t k;
    
    rec_t adjust(rec_t a, rec_t b) {
        if (a.first == b.first) 
            return make_pair(a.first, a.second + b.second);
        
        if (a.second < b.second) swap(a, b);
        
        return make_pair(a.first, a.second - b.second);
    }
    
    rec_t get_dom_internal(int a, int b, int i, int p, int q) {
        if (a <= p && q <= b) return vals[i];
        
        int s = (p + q) / 2;
        rec_t result = make_pair(0, 0);
        
        if (a <= s) result = adjust(result, get_dom_internal(a, b, 2*i, p, s));
        if (b > s) result = adjust(result, get_dom_internal(a, b, 2*i+1, s+1, q));
        
        return result;
    }
public:
    DomTree(const vector<int> &v) : k(1) {
        while(k < v.size()) k <<= 1;
        
        vals.resize(2 * k);
        for (size_t i = 0; i < v.size(); i++)
            vals[k + i] = make_pair(v[i], 1);
        for (size_t i = k - 1; i > 0; i--) 
            vals[i] = adjust(vals[2 * i], vals[2 * i + 1]);
    }
    
    int get_dom_cand(int a, int b) {
        return get_dom_internal(a, b, 1, 1, k).first;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> p(n);
    for (int &i : p) cin >> i;
    
    DomTree t(p);
    vector< set<pair<int, int>> > on_prefix(n + 1, { make_pair(0, 0) });
    
    for (int i = 0; i < n; i++)
        on_prefix[p[i]].insert({ 
            i + 1, 
            (--on_prefix[p[i]].end())->second + 1 
        });
    
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        
        int cand = t.get_dom_cand(a, b);
        int cnt = (--on_prefix[cand].upper_bound({b + 1, -1}))->second -
                  (--on_prefix[cand].upper_bound({a, -1}))->second;
        
        if (2 * cnt > (b - a + 1)) 
            cout << cand << endl;
        else
            cout << 0 << endl;
    }
    
    return 0;
}
