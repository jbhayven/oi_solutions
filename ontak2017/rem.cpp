#include <bits/stdc++.h>
using namespace std;

struct Crossroad {
    struct HLD {
        set<int> blocked;
        Crossroad *parent;
        int size;
        
        HLD() :
            blocked(),
            parent(nullptr),
            size(0)
        {}
    };
    
    list<Crossroad*> edges;
    Crossroad *parent;
    HLD *branch;
    int depth;
    
    Crossroad() :
        edges(),
        parent(nullptr),
        branch(nullptr),
        depth(0)
    {}
    
    void preprocess() {
        depth++;
        
        for (Crossroad *e : edges) {
            if (e == parent) continue;
            
            e->parent = this;
            e->depth = depth;
            e->preprocess();
            
            if (branch == nullptr || branch->size < e->branch->size)
                branch = e->branch;
        }
        
        if (branch == nullptr) 
            branch = new HLD();
            
        branch->size++;
        branch->parent = parent;
    }

    void close() {
        branch->blocked.insert(depth);
    }

    void open() {
        branch->blocked.erase(depth);
    }
};

bool test(Crossroad *a, Crossroad *b) {
    while (a->branch != b->branch) {
        if (a->branch->parent == nullptr)
            swap(a, b);
        else if (b->branch->parent == nullptr) 
            {}
        else if (a->branch->parent->depth < b->branch->parent->depth)
            swap(a, b);
        
        if (!a->branch->blocked.empty() && 
            *a->branch->blocked.begin() <= a->depth)
            return false;
        
        a = a->branch->parent;
    }
    
    if (a->depth < b->depth)
        swap(a, b);
        
    auto nearest_blocked = b->branch->blocked.lower_bound(b->depth);
    
    if (nearest_blocked == b->branch->blocked.end())
        return true;
        
    return (*nearest_blocked > a->depth);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n;
    vector<Crossroad> city;
    
    cin >> n;
    
    city.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        city[a].edges.push_back(&city[b]);
        city[b].edges.push_back(&city[a]);
    }
    
    city[1].preprocess();
    
    int q; cin >> q; while(q--) {
        char c; cin >> c;
        int a, b;
        
        switch(c) {
        case '-':
            cin >> a;
            city[a].close();
            break;
        case '+':
            cin >> a;
            city[a].open();
            break;
        case '?':
            cin >> a >> b;
            if (test(&city[a], &city[b]))
                cout << "TAK\n";
            else
                cout << "NIE\n";
        }
    }
    
    return 0;
}
