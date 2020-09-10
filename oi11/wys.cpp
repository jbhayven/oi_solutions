#include <bits/stdc++.h>
using namespace std;

class Tree {
    int result;
    int mod;
    Tree *left, *right;

    inline int real_result() {
        return result + mod;
    }
    
    inline void push_down() {
        if (left == nullptr) {
            left = new Tree();
            right = new Tree();
        }
        
        left->mod += mod;
        right->mod += mod;
        mod = 0;
    }
    
    inline void recreate() {
        result = min(left->real_result(), right->real_result());
    }

public:
    Tree() :
        result(0), mod(0), 
        left(nullptr), right(nullptr)
    {}
    
    int add(int a, int b, int chng, int l, int r, const vector<int> &pts) {
        if (a <= pts[l] && pts[r] <= b) {
            mod += chng;
            return real_result();
        }
        
        push_down();
        
        int s = (l + r) / 2;
        int result = 0;
        if (a <= pts[s])
            result = max(result, left->add(a, b, chng, l, s, pts));
        if (b >= pts[s+1])
            result = max(result, right->add(a, b, chng, s+1, r, pts));
        
        recreate();
        
        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n;
    vector< pair<int, pair<int, int> > > walls;
    set<int> vert_coords;
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        int k; cin >> k;
        vector<int> coords(k);
        for (int &coord : coords)
            cin >> coord;
        for (int i = 0; i < k / 2; i++) {
            walls.push_back({
                coords[2 * i],
                {
                    coords[(2 * i - 1 + k) % k], 
                    coords[2 * i + 1]
                }
            });
        }
        for (int i = 0; i < k / 2; i++)
            vert_coords.insert(coords[2 * i + 1]);
    }
    
    sort(walls.begin(), walls.end());
    
    Tree *t = new Tree();
    int result = 0;
    vector<int> pts(vert_coords.begin(), vert_coords.end());
    for (auto w : walls) {
        int type;
        if (w.second.first < w.second.second) 
            type = -1;
        else {
            swap(w.second.first, w.second.second);
            type = 1;
        }
        result = max(result, t->add(w.second.first, w.second.second, type, 0, pts.size() - 1, pts));
    }
    
    cout << result << endl;
    return 0;
}
