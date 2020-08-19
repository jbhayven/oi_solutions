#include <bits/stdc++.h>
using namespace std;

/* Eats up a lot of memory, too much for this problem */

class Tree {
// Multidimensional tree
private:
    Tree *left, *right;
    int l, r;
    int value;
    Tree *deleg;
    
    void touch_left() {
        if (left == nullptr) 
            left = new Tree(l, (l+r)/2, this);
    }
    
    void touch_right() {
        if (right == nullptr)
            right = new Tree((l+r)/2+1, r, this);
    }
    
public:
    Tree(int l, int r) :
        left(nullptr),
        right(nullptr),
        l(l), r(r),
        value(INT_MAX),
        deleg(nullptr)
    {}
    
    template<class... Args>
    Tree(int l, int r, int p, Args... args) : 
        Tree(l, r)
    {
        deleg = new Tree(p, args...);
    }
    
    Tree(int l, int r, Tree *t) :
        Tree(l, r) {
            
        if (t->deleg != nullptr)
            deleg = new Tree(t->deleg);
        else
            deleg = nullptr;
    }
    
    Tree (Tree *t) :
        Tree(t->l, t->r, t)
    {}
    
    int get(int x) {
        int ret = value;
        
        if (x <= (l + r) / 2 && left != nullptr)
            ret = min(ret, left->get(x));
        if (x > (l + r) / 2 && right != nullptr)
            ret = min(ret, right->get(x));
            
        return ret;
    }
    
    /***
     * get (a, b, c, d, e...) – get result at coords {a, b, c, d, e...}
     */
    template<class... Args>
    int get(int x, int y, Args... args) {
        int res = INT_MAX;
        
        if (deleg != nullptr) 
            res = deleg->get(y, args...);
        
        if (x <= (l + r) / 2 && left != nullptr)
            res = min(res, left->get(x, y, args...));
        if (x > (l + r) / 2 && right != nullptr)
            res = min(res, right->get(x, y, args...));
        
        return res;
    }
    
    void finalize_add(int val) {
        value = min(value, val);
    }
    
    template<class... Args>
    void finalize_add(int val, int p, Args... args) {
        deleg->add(val, p, args...);
    }
    
    /***
     * add (val, a1, a2, b1, b2...) – 
     * set value to min(value, val) at range {(a1, a2), (b1, b2), ...}
     */
    template<class... Args>
    void add(int val, int p, int q, Args... args) {
        if (p <= l && r <= q) {
            finalize_add(val, args...);
            return;
        }
        
        int s = (l + r) / 2;
        if (p <= s) {
            touch_left();
            left->add(val, p, q, args...);
        }
        if (q >= s+1) {
            touch_right();
            right->add(val, p, q, args...);
        }
    }
    
    ~Tree() {
        if (left != nullptr) delete left;
        if (right != nullptr) delete right;
        if (deleg != nullptr) delete deleg;
    }
};
    
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
        
    struct wyd {
        int a;
        int x;
        int y;
        int result;
    } events[200100];
    
    int q; cin >> q;
    
    for (int i = 0; i < q; i++) {
        cin >> events[i].a >> events[i].x >> events[i].y;
        events[i].result = INT_MAX;
    }

#define rot_90(ev)                                                             \
    swap(ev.x, ev.y);                                                          \
    ev.y = 200010 -ev.y;                                                       \
    
    for (int t = 4; t > 0; t--) {
        Tree *tree = new Tree(0, 200010, 0, 200010);
        for (int i = 0; i < q; i++) {
            if (events[i].a == 1) {
                tree->add(events[i].x + events[i].y, 
                        0, events[i].x,
                        0, events[i].y);
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
