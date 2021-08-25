#include <bits/stdc++.h>
using namespace std;

class Tree {
    size_t k;
    vector< int > pts;
    vector< pair<int, int> > result;
    vector< int > bonus;
    
    inline pair<int, int> real(int i) {
        return {result[i].first, result[i].second + bonus[i]};
    }
    
    void push(int i) {
        bonus[2 * i] += bonus[i];
        bonus[2 * i + 1] += bonus[i];
        result[i].second += bonus[i];
        
        bonus[i] = 0;
    }
    
    inline pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
        if (a.second < b.second)
            swap(a, b);
            
        if (a.second == b.second) {
            return { a.first + b.first, a.second };
        } else {
            return a;
        }
    }
    
    inline void suck(int i) {
        auto l = real(2 * i);
        auto r = real(2 * i + 1);
        
        result[i] = combine(l, r);
    }
    
    pair<int, int> add_get(int a, int b, int val, int i, int p, int q) {
        if (a <= pts[p-1] && pts[q] <= b) {
            bonus[i] += val;
            return real(i);
        }
        
        push(i);
        
        int mid = (p + q) / 2;
        
        pair<int, int> result = {0, 0};
        if (a < pts[mid]) result = combine(result, add_get(a, b, val, 2*i, p, mid));
        if (b > pts[mid]) result = combine(result, add_get(a, b, val, 2*i+1, mid + 1, q));
        
        suck(i);
        
        return result;
    }
    
public:
    Tree(vector<int> &pts) : k(1), pts(pts) {
        size_t size = pts.size() - 1;
        
        while (k <= size) k <<= 1;
    
        result.resize(2 * k, {0, 0});
        bonus.resize(2 * k, 0);
        this->pts.resize(2 * k, 1e9 + 1000);
        
        for (size_t i = 0; i < k; i++) {
            result[k + i] = { this->pts[i + 1] - this->pts[i], 0 };
        }
        
        for (int i = k - 1; i > 0; i--) {
            suck(i);
        }
    }
    
    void add(int a, int b) {
        if (a >= b) return;
        
        add_get(a, b, 1, 1, 1, k);
    }
    
    void take(int a, int b) {
        if (a >= b) return;
        
        add_get(a, b, -1, 1, 1, k);
    }
    
    pair<int, int> get_all() {
        return real(1);
    }
};

int64_t solve(vector< pair<int, int> > &ranges, int width) {
    vector<int> coords({0, width});
    
    for (auto rng : ranges) {
        coords.push_back(rng.first);
        coords.push_back(rng.second);
    }
    
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    
    Tree t(coords);
    
    vector<pair<int, int>> changes;
    
    for (auto &rng : ranges) {
        if (rng.first > rng.second) 
            swap(rng.first, rng.second);
            
        if (rng.first > 0) {
            t.add(0, rng.first);
            t.add(rng.second, width);
            changes.push_back(rng);
            changes.push_back({rng.second, width});
        } else {
            t.add(0, rng.second);
            changes.push_back({rng.second, width});
        }
    }
    
    sort(changes.begin(), changes.end(), greater<pair<int, int>>());
    
    int result = t.get_all().first;
    
    coords.pop_back();
    for (int pt : coords) {
        while (!changes.empty() && changes.back().first == pt) {
            auto rng = changes.back(); changes.pop_back();
            t.take(0, rng.first);
            t.take(rng.second, width);
            t.add(rng.first, rng.second);
        }
        
        result = max(result, t.get_all().first);
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, dim_x, dim_y;
    cin >> n >> dim_x >> dim_y;
    
    vector< pair<int, int> > x(n), y(n);
    
    for (int i = 0; i < n; i++) 
        cin >> x[i].first >> y[i].first >> x[i].second >> y[i].second;
    
    cout << solve(x, dim_x) * solve(y, dim_y) << endl;
    
    return 0;
}
