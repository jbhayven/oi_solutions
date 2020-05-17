#include <bits/stdc++.h>
using namespace std;

class FindUnion {
    FindUnion* par;         // parent structure
    int size;               // size of structure (number of nodes)
    unordered_set<int> adj; // set of nodes neighboring with the structure
                            // (if size > 1, it will also contain all nodes
                            // belonging to the structure) 
    
public:
    FindUnion() :
        par(this),
        size(1)
    {}
    
    void make_adj(const vector<int> &edges) {
        adj = unordered_set<int>(edges.begin(), edges.end());
    }
    
    FindUnion* f() {
        return par = (par == this) ? this : par->f(); 
    }
    
    FindUnion* u(FindUnion* other) {
        auto f1 = this->f();
        auto f2 = other->f();
        
        if(f1 == f2) return f1;
        
        if(f1->size < f2->size)
            swap(f1, f2);
        
        f2->par = f1;
        f1->size += f2->size;
        f1->adj.merge(f2->adj);
        return f1;
    }
    
    bool is_adj(int v) const {
        return adj.find(v) != adj.end();
    }
};


const int MAX_N = 500100;
vector<FindUnion*> v;
vector<int> e[MAX_N];
vector<bool> occ;

int n, m, q;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); 
    
    /* Read and initialize */
    cin >> n >> m;
    
    v = vector<FindUnion*>(n + 2);
    occ = vector<bool>(n + 2);
    
    generate(v.begin(), v.end(), [](){ return new FindUnion(); });
    for(int i = 1; i <= n; i++) {
        bool val;
        cin >> val;
        occ[i] = val;
    }
    
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        e[a].push_back(b);
        e[b].push_back(a);
    }
    
    /* Initialize the rest */
    for(int i = 1; i <= n; i++)
        v[i]->make_adj(e[i]);
        
    for(int i = 1; i <= n; i++)
        for(int neigh : e[i])
            if (occ[i] == false && occ[neigh] == false)
                v[i]->u(v[neigh]);
        
    cin >> q;
    
    for(int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        
        if(occ[b] == false && (a == b || v[b]->f()->is_adj(a))) {
            cout << "YES\n";
            occ[a] = false;
            for(int neigh : e[a])
                if(occ[neigh] == false)
                    v[a]->u(v[neigh]);
        }
        else 
            cout << "NO\n";
    }
    
    return 0;
}
