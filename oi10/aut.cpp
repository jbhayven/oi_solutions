#include <bits/stdc++.h>
using namespace std;
using highway_t = pair<int, int>;

/* T = comparison class */
template<template<typename> typename T>
class Tree {
    using entry_info = pair<int, const highway_t*>;
    
    const int OOR; /* = OUT_OF_RANGE, a very small value in the order dictated by T */
    const entry_info EMPTY_ENTRY; /* = {OUT_OF_RANGE, nullptr} */
    vector< entry_info > range_vals;
    vector< set<entry_info, T<entry_info>> > leaves;
    size_t size;
    
    template<typename U>
    inline U comped(U a, U b) {
        return T<U>()(a, b) ? b : a;
    }
    
    inline void update(size_t pos) {
        range_vals[pos] = comped(range_vals[2 * pos], range_vals[2 * pos + 1]);
    }
    
    entry_info get_internal(int a, int b, int i, int p, int q) {
        if (a <= p && q <= b) 
            return range_vals[i];
        
        entry_info ret = EMPTY_ENTRY;
        
        int s = (p + q) / 2;
        if (a <= s) ret = comped(ret, get_internal(a, b, 2*i, p, s));
        if (b > s) ret = comped(ret, get_internal(a, b, 2*i+1, s+1, q));
        
        return ret;
    }
    
    int get_key(const highway_t *a) {
        return T<int>()(a->first, a->second) ? a->first : a->second;
    }
    
    int get_value(const highway_t *a) {
        return T<int>()(a->first, a->second) ? a->second : a->first;
    }
    
    void pull_from_leaf(int key) {
        auto entry = leaves[key].empty() ? EMPTY_ENTRY : *leaves[key].rbegin();
        
        size_t pos = size + key - 1;
        range_vals[pos] = entry;
        
        while (pos) {
            pos >>= 1;
            update(pos);
        }
    }
    
    Tree() :
        OOR(comped(INT_MIN, INT_MAX) == INT_MIN ? INT_MAX : INT_MIN),
        EMPTY_ENTRY(make_pair(OOR, nullptr))
    {}
    
public:
    void add(const highway_t *a) {
        int key = get_key(a);
        int value = get_value(a);

        leaves[key].insert(make_pair(value, a));
        pull_from_leaf(key);
    }
    
    void remove(const entry_info &info) {
        int key = get_key(info.second);
        
        leaves[key].erase(info);
        pull_from_leaf(key);
    }
    
    entry_info get_extreme(int a, int b) {
        if (a > b) return EMPTY_ENTRY;
        
        return get_internal(a, b, 1, 1, size);
    }
    
    Tree(size_t s) : Tree() {
        size = 1; while(size < s) size <<= 1;
        
        range_vals.resize(2 * size, {OOR, nullptr});
        leaves.resize(2 * size);
    }
    
    Tree(size_t len, const vector<highway_t> &h) : Tree(len) {
        for (const highway_t &a : h) add(&a);
    }
};

class DFS_splitter {
    size_t n;
    vector<highway_t> highways;
    unordered_map<const highway_t*, int> mapped; 
    
    void do_DFS(const highway_t *h, int i, 
                Tree<less> &max_tree, 
                Tree<greater> &min_tree) 
    {
        mapped[h] = i;
        pair<int, const highway_t*> entry;
        
        int a = h->first;
        int b = h->second;
        
        if (a + 1 > b - 1) return;
        
        while ((entry = max_tree.get_extreme(a + 1, b - 1)).first > b) {
            max_tree.remove(entry);
            
            if (!mapped.count(entry.second))
                do_DFS(entry.second, 1 - i, max_tree, min_tree);
        }
        
        while ((entry = min_tree.get_extreme(a + 1, b - 1)).first < a) {
            min_tree.remove(entry);
            
            if (!mapped.count(entry.second))
                do_DFS(entry.second, 1 - i, max_tree, min_tree);
        }
    }
    
    bool verify_private(int type) {
        Tree<less> max_tree(n);
        Tree<greater> min_tree(n);
        
        for (const highway_t &h : highways) {
            if (mapped[&h] != type) continue;
            
            int a = h.first;
            int b = h.second;
            
            if (max_tree.get_extreme(a + 1, b - 1).first > b)
                return false;
                
            if (min_tree.get_extreme(a + 1, b - 1).first < a)
                return false;
                
            max_tree.add(&h);
            min_tree.add(&h);
        }
        
        return true;
    }
    
public:
    void split() {
        Tree<less> max_tree(n, highways);
        Tree<greater> min_tree(n, highways);
        
        for (const auto &h : highways)
            if (!mapped.count(&h))
                do_DFS(&h, 0, max_tree, min_tree);
    }
    
    /* Call only after split */
    bool verify() {
        return verify_private(0) && verify_private(1);
    }
    
    vector<bool> get_split() {
        vector<bool> result;
        for (const auto &h : highways) 
            result.push_back(mapped[&h] == 1 ? true : false);
        return result;
    }

    DFS_splitter(size_t n, vector<highway_t> &&h) :
        n(n),
        highways(h),
        mapped()
    {}
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, k;
    cin >> n >> k;
    
    vector<highway_t> highways(k);
    for (auto &h : highways) cin >> h.first >> h.second;
    
    /* Transfer ownership of vector contents */
    DFS_splitter solve(n, move(highways));
    
    solve.split();
    if (!solve.verify()) {
        cout << "NIE" << endl;
    } else {
        vector<bool> split = solve.get_split();
        for (bool val : split) 
            cout << (val ? 'N' : 'S') << '\n';
    }
    
    return 0;
}
