#include <bits/stdc++.h>
using namespace std;

class Treap {
    long long seed;
    int val;
    Treap *left;
    Treap *right;
    bool rev;
    size_t size;
    
    void touch() {
        if (!rev) return;
        
        assemble(right, left);

        if (left != nullptr) left->flip();
        if (right != nullptr) right->flip();
        
        rev = false;
    }
    
    Treap* assemble(Treap *left, Treap *right) {
        this->left = left;
        this->right = right;
        
        size = 1 + get_size(left) + get_size(right);
        
        return this;
    }
    
    static inline size_t get_size(Treap *t) {
        if (t == nullptr) return 0;
        return t->size;
    }
    
    Treap* add_greater(Treap *other) {
        if (other == nullptr) return this;
        other->touch();
        this->touch();
        
        if (seed < other->seed) {
            return other->assemble(this->add_greater(other->left), other->right);
        } else {
            if (this->right == nullptr)
                return this->assemble(this->left, other);
            else
                return this->assemble(this->left, this->right->add_greater(other));
        }
    }
public:
    Treap () : 
        seed((long long) std::rand() * INT_MAX + std::rand()),
        left(nullptr), right(nullptr),
        rev(false), size(1)
    {}
    
    Treap (int val) : Treap() { this->val = val; }
    
    void set_val(int val) {
        this->val = val;
    }
    
    int get_val() const {
        return val;
    }
    
    void flip() {
        this->rev = !this->rev;
    }
    
    static Treap* merge(Treap *l, Treap *r) {
        if (l == nullptr) return r;
        return l->add_greater(r);
    }
    
    pair<Treap*, Treap*> split_n_smallest(size_t n) {
        if (n == 0) return make_pair(nullptr, this);
        
        this->touch();
        
        if (get_size(this->left) >= n) {
            auto rec = this->left->split_n_smallest(n);
            return make_pair(rec.first, this->assemble(rec.second, this->right));
        } else {
            auto rec = this->right->split_n_smallest(n - get_size(this->left) - 1);
            return make_pair(this->assemble(this->left, rec.first), rec.second);
        }
    }
};

Treap* generate_treap (const vector<int> &order) {
    Treap* root = new Treap(order[0]);
    for (size_t i = 1; i < order.size(); i++) 
        root = Treap::merge(root, new Treap(order[i]));
    
    return root;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, q;
    cin >> n >> q;
    
    vector<int> order(n);
    for (int &i : order)
        cin >> i;
        
    Treap* t = generate_treap(order);
    
    auto query = [&](int l, int r, std::function<void(Treap*)>func) {
        auto leftmid_right = t->split_n_smallest(r);
        auto left_mid = leftmid_right.first->split_n_smallest(l - 1);
            
        func(left_mid.second);
            
        t = Treap::merge(Treap::merge(left_mid.first, 
                                      left_mid.second), 
                         leftmid_right.second);
    };
    
    while (q--) {
        char type; cin >> type;
        
        if (type == 'Q') {
            int which; cin >> which;
            query(which, which, [](Treap *t){ cout << t->get_val() << endl; });
        } else {
            int l, r; cin >> l >> r;
            query(l, r, [](Treap *t){ t->flip(); });
        }
    }
    
    return 0;
}
