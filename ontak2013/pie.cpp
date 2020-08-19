#include <bits/stdc++.h>
using namespace std;

struct Component;

struct Pair_info {
    int left, right;
    vector<Pair_info*> rej_force;
    Pair_info *alt;
    Component *comp;
    
    Pair_info(int x, int y) : left(x), right(y), alt(nullptr) {}
};

vector<Pair_info*> get_pair_info(const vector<int> &nums) {
    unordered_map<int, vector<int>> pos;
    for (size_t i = 0; i < nums.size(); i++)
        pos[nums[i]].push_back(i);
        
    vector<Pair_info*> pairs;
        
    for (auto &ent : pos) {
        switch (ent.second.size()) {
        case 2: 
            pairs.push_back(new Pair_info(ent.second[0], ent.second[1]));
            
            break;
        case 4:
            pairs.push_back(new Pair_info(ent.second[0], ent.second[1]));
            pairs.push_back(new Pair_info(ent.second[2], ent.second[3]));
            pairs.push_back(new Pair_info(ent.second[0], ent.second[2]));
            pairs.push_back(new Pair_info(ent.second[1], ent.second[3]));
            
            pairs.end()[-1]->alt = pairs.end()[-2];
            pairs.end()[-2]->alt = pairs.end()[-1];
            
            pairs.end()[-3]->alt = pairs.end()[-4];
            pairs.end()[-4]->alt = pairs.end()[-3];
            
            for (int i : {-2, -1}) {
                for (int j : {-3, -4}) {
                    pairs.end()[i]->rej_force.push_back(pairs.end()[j]);
                    pairs.end()[j]->rej_force.push_back(pairs.end()[i]);
                }
            }
            
            break;
        default:
            cout << "NIE" << endl;
            exit(0);
        }
    }
    
    return pairs;
}

struct Tree {
    struct Extr_info {
        Pair_info* min_pair;
        Pair_info* max_pair;
        
        void update(const Extr_info &other) {
            if (min_pair == nullptr || 
                (other.min_pair != nullptr && min_pair->right > other.min_pair->right))
                min_pair = other.min_pair;
                
            if (max_pair == nullptr || 
                (other.max_pair != nullptr && max_pair->right < other.max_pair->right))
                max_pair = other.max_pair;
        }
    };
    
    vector<Extr_info> tree_info;
    vector<Pair_info*> orig_ptr;
    vector<int> x;
    size_t k;
    
    Tree (vector<Pair_info*> &pairs) {
        sort (pairs.begin(), pairs.end(), [](Pair_info* l, Pair_info* r){ return l->left < r->left; });
        orig_ptr = pairs;
        
        k = 1; while(k < pairs.size()) k *= 2;
        for (auto p : pairs) 
            x.push_back(p->left);
        while (x.size() < k) x.push_back(1000000);
        tree_info.resize(2*k);
        
        for (size_t i = 0; i < pairs.size(); i++)
            tree_info[k + i] = Extr_info({ .min_pair = pairs[i], .max_pair = pairs[i] });
        
        for (size_t i = k-1; i > 0; i--) {
            tree_info[i] = tree_info[2*i];
            tree_info[i].update(tree_info[2*i+1]);
        }
    }
    
    Extr_info get_extremes(int a, int b, int i = 1, int p = 0, int q = -1) {
        if (q == -1) q = k-1;
        
        if (q < (int) x.size() && a <= x[p] && x[q] <= b) 
            return tree_info[i];
        
        int s = (p + q) / 2;
        
        Extr_info result{ .min_pair = nullptr, .max_pair = nullptr };
        
        if (a <= x[s]) result.update(get_extremes(a, b, 2*i, p, s));
        if (b >= x[s+1]) result.update(get_extremes(a, b, 2*i+1, s+1, q));
        
        return result;
    }
    
    void add_remove_pair(Pair_info *p, bool make_be) {
        size_t l = 0;
        size_t r = x.size() - 1;
        
        while(l != r) {
            size_t s = (l + r) / 2;
            if (x[s] < p->left) l = s+1;
            else r = s;
        }
        
        while(l < x.size() && x[l] == p->left) {
            if (orig_ptr[l] == p) {
                if (make_be) {
                    tree_info[k+l].min_pair = p;
                    tree_info[k+l].max_pair = p;
                } else {
                    tree_info[k+l].min_pair = nullptr;
                    tree_info[k+l].max_pair = nullptr;
                }
                size_t pos = (k+l) / 2;
                while(pos > 0) {
                    tree_info[pos] = tree_info[2*pos];
                    tree_info[pos].update(tree_info[2*pos + 1]);
                    pos /= 2;
                } 
                break;
            }
            l++;
        }
    }
};

void first_dfs(Pair_info* p, unordered_set<Pair_info*> &visited, Tree &t, const std::function<void(Pair_info*)> &fun) {
    visited.insert(p);
    
    if (p->alt != nullptr && visited.find(p->alt) == visited.end())
        first_dfs(p->alt, visited, t, fun);
    
    while (true) { // get all pairs that start here and end here (too early)
        auto info = t.get_extremes(p->left, p->right); 
        if (info.min_pair == nullptr) break; 
        if (info.min_pair->right >= p->right) break; // ok
        
        t.add_remove_pair(info.min_pair, false); // won't be needed anymore
        for (Pair_info* q : info.min_pair->rej_force) {
            if (visited.find(q) == visited.end())
                first_dfs(q, visited, t, fun);
        }
    }
    
    while (true) { // get all pairs that start before and end later (too late)
        auto info = t.get_extremes(0, p->left); 
        if (info.max_pair == nullptr) break;    
        if (info.max_pair->right <= p->right) break; // ok
        
        t.add_remove_pair(info.max_pair, false); // won't be needed anymore
        for (Pair_info* q : info.max_pair->rej_force) {
            if (visited.find(q) == visited.end())
                first_dfs(q, visited, t, fun);
        }
    }
    
    fun(p);
}

void second_dfs(Pair_info* p, unordered_set<Pair_info*> &visited, Tree &t, const std::function<void(Pair_info*)> &fun) {
    visited.insert(p);
    if (p->alt != nullptr && visited.find(p->alt) == visited.end())
        second_dfs(p->alt, visited, t, fun);
    
    for (Pair_info* q : p->rej_force) {
        while (true) { // get all pairs that start here and end here (too early)
            auto info = t.get_extremes(q->left, q->right); 
            if (info.min_pair == nullptr) break;
            if (info.min_pair->right >= q->right) break; // ok
            
            t.add_remove_pair(info.min_pair, false); // won't be needed anymore
            if (visited.find(info.min_pair) == visited.end())
                second_dfs(info.min_pair, visited, t, fun);
        }
        
        while (true) { // get all pairs that start before and end later (too late)
            auto info = t.get_extremes(0, q->left); 
            if (info.max_pair == nullptr) break;    
            if (info.max_pair->right <= q->right) break; // ok
            
            t.add_remove_pair(info.max_pair, false); // won't be needed anymore
            if (visited.find(info.max_pair) == visited.end())
                second_dfs(info.max_pair, visited, t, fun);
        }
    }
    
    fun(p);
}

struct Component {
    vector<Pair_info*> pairs;
    bool considered;
    bool added;
    
    Component() : considered(false), added(false) {}
};

bool is_ok(Pair_info *p, Tree &t) {
    bool left = false;
    bool right = false;
     
    auto info = t.get_extremes(p->left, p->right); 
    if (info.min_pair == nullptr || 
        info.min_pair->right >= p->right) left = true; 
            
    info = t.get_extremes(0, p->left); 
    if (info.max_pair == nullptr ||
        info.max_pair->right <= p->right) right = true;
    
    return left && right;
}

void try_add(Component *c, Tree &t) {
    c->considered = true;
    
    bool fail = false;
    
    for (auto p : c->pairs) {
        if (is_ok(p, t)) {
            t.add_remove_pair(p, true);
        } else {
            fail = true;
            break;
        }
    }
        
    if (fail) {
        for (auto p : c->pairs)
            t.add_remove_pair(p, false);
        c->added = false;
    } else {
        c->added = true;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    size_t n;
    vector<int> nums;
    
    cin >> n;
    nums.resize(n);
    for (int &i : nums) cin >> i;
    
    auto pairs = get_pair_info(nums);
    
    Tree t(pairs); // sorts pairs
    unordered_set<Pair_info*> visited;
    vector<Pair_info*> anti_topological;
    auto fun = [&](Pair_info *p){ anti_topological.push_back(p); };
    for (auto p : pairs) if (visited.find(p) == visited.end()) 
        first_dfs(p, visited, t, fun);

    t = Tree(pairs); // sorts pairs
    visited.clear();
    vector<Component*> comps;
    while (!anti_topological.empty()) {
        auto p = anti_topological.back(); anti_topological.pop_back();
        if (visited.find(p) != visited.end()) continue;
        comps.push_back(new Component());
        auto fun = [&](Pair_info *p) {
            p->comp = comps.back();
            comps.back()->pairs.push_back(p); 
        };
        second_dfs(p, visited, t, fun);
    }
    
    for (auto p : pairs) t.add_remove_pair(p, false);
    for (auto p : pairs) if (p->alt == nullptr && p->comp->considered == false)
        try_add(p->comp, t);
    
    while (!comps.empty()) {
        if (comps.back()->considered == false) 
            try_add(comps.back(), t);
        comps.pop_back();
    }
    
    vector<Pair_info*> added_pairs;
    for (auto p : pairs) if (p->comp->added)
        added_pairs.push_back(p); // pairs are sorted so added_pairs are as well
        
    if (added_pairs.size() * 2 < n) cout << "NIE" << endl;
    else {
        cout << "TAK" << endl;
        for (auto p : added_pairs)
            cout << nums[p->left] << " "; 
        cout << endl;
    }
    
    return 0;
}
