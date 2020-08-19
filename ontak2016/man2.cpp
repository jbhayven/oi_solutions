#include <bits/stdc++.h>
using namespace std;

#define MAX_N 200100
#define MAX_DIM 200100

class Tree {
// A fast and memory-efficient two-dimensional tree
private:
    struct One_dimension {
        set <pair<int, int>> min_diags;
        
        void insert(pair<int, int> p) {
            if (min_diags.empty()) // init
                min_diags = {{INT_MIN, INT_MIN}, {INT_MAX, INT_MAX}};
            
            pair<int, int> comp_p = {p.first - 1, INT_MAX};
            if (min_diags.upper_bound(comp_p)->second <= p.second) return;
            
            comp_p = {p.first, INT_MAX};
            while((--min_diags.upper_bound(comp_p))->second >= p.second)
                min_diags.erase(--min_diags.upper_bound(comp_p));
            
            min_diags.insert(p);
        }
        
        int get(int x) {
            if (min_diags.empty()) // init
                min_diags = {{INT_MIN, INT_MIN}, {INT_MAX, INT_MAX}};
                
            return min_diags.lower_bound({x, 0})->second;
        }
    } second_dim[MAX_DIM + 10];

public:
    void insert(int x, int y) {
        int val = (x + y);
        
        while (x > 0) {
            second_dim[x].insert({y, val});
            x -= (x & -x);
        }
    }
    
    int get(int x, int y) {
        int res = INT_MAX;
        
        while (x < MAX_DIM) {
            res = min(res, second_dim[x].get(y));
            x += (x & -x);
        }
        
        return res;
    }
};
    
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
        
    struct wyd {
        int a;
        int x;
        int y;
        int result;
    } events[MAX_N];
    
    int q; cin >> q;
    
    for (int i = 0; i < q; i++) {
        cin >> events[i].a >> events[i].x >> events[i].y;
        events[i].result = INT_MAX;
    }

#define rot_90(ev)                                                             \
    swap(ev.x, ev.y);                                                          \
    ev.y = MAX_DIM - ev.y;                                                     \
    
    for (int t = 4; t > 0; t--) {
        Tree *tree = new Tree();
        for (int i = 0; i < q; i++) {
            if (events[i].a == 1) {
                tree->insert(events[i].x, events[i].y);
            } else {
                int pos = events[i].x + events[i].y;
                int nearest = tree->get(events[i].x, events[i].y);
                events[i].result = min(events[i].result, nearest - pos);
            }
            rot_90(events[i])
        }
        delete tree;
    }
    
    for (int i = 0; i < q; i++) 
        if (events[i].a == 2)
            cout << events[i].result << endl;
    
    return 0;
}
