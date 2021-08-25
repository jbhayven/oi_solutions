#include <bits/stdc++.h>
using namespace std;

template<class T>
class treap {
    using tree = treap*;
    
    tree left, right;
    T val, sum;
    int64_t seed;
    
    static const int MAX_N = 4e5 + 10;
    static treap nodes[MAX_N];
    static int node_cnt;
    
    treap(T val) :
        left(nodes),
        right(nodes),
        val(val),
        sum(val),
        seed(std::rand())
    {}
    
    void append(tree left, tree right) {
        this->left = left;
        this->right = right;
        this->sum = left->sum + right->sum + val;
    }

public:
    static void init() {
        nodes = 0;
        nodes[0].val();
        nodes[0].sum();
    }
    
    static tree create_node(T val) {
        nodes[++node_cnt] = treap(val);
        return nodes + node_cnt;
    }
    
    tree min() {
        if (left != NULL) return left->min();
        return this;
    }
    
    tree max() {
        if (right != NULL) return right;
        return this;
    }
        
    static tree combine(tree left, tree right) {
        if (left == NULL) return right;
        if (right == NULL) return left;
        
        if (left->seed < right->seed) swap(left, right);
        
        if (left->val < right->val) {
            left->append(left->left, combine(left->right, right));
        } else {
            left->append(combine(left->left, right), left->right);
        }
        
        return left;
    }
        
    pair<tree, tree> split(T mid, T sum = 0) {
        T temp = sum;
        temp += this->val;
        
        if (temp < mid) {
            auto sub = this->right->split(mid, temp);
            return { this->append(this->left, sub.first), sub.second };
        } else {
            auto sub = this->left->split(mid, temp);
            return { sub.first, this->append(sub.second, this->right) };
        }
    }
    
    tree insert(T val) {
        tree node = create_node(val);
        return combine(this, node);
    }
};

struct segment {
    int x, y;
    
    segment() : x(0), y(0) {}
    segment(int x, int y) : x(x), y(y) {}
    
    void simplify() {
        int gcd = __gcd(x, y);
        x /= gcd;
        y /= gcd;
    }
    
    segment& operator+=(const segment &other) {
        x += other.x;
        y += other.y;
    
        return *this;
    }
    
    bool operator<(const segment &other) const {
        int64_t l = (int64_t) x * other.y;
        int64_t r = (int64_t) other.x * y;
        
        return l < r;
    }
};


const int MAX_N = 121000;

bool villain[MAX_N];
vector<int> graph[MAX_N];

void add(treap<segment> st, segment s) {
    while (st->first()->val < s) {
        s += st->first()->val;
        auto [unused, st] = st->split(st->first()->val, segment());
    }
    st->insert(s);
}

treap<segment> get_propos(int i, int p = -1) {
    treap<segment> result = treap(segment(1, 0));
    
    for (auto j : graph[i]) {
        if (j == p) continue;
        
        auto new_propos = get_propos(j, i);
        
        if (villain[i]) {
            add(new_propos, segment(1, 0));
            all_propos.insert(new_propos);
            continue;
        }
        
        if (result.size() < new_propos.size())
            result.swap(new_propos);
        
        result.insert(new_propos.begin(), new_propos.end());
    }
    
    segment new_segment;
    
    if (!villain[i]) {
        add(result, segment(graph[i].size() - (p != -1) - 1, 1));
    }
       
    return result;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    treap::init();
    
    int n; cin >> n; 
    
    string rel; cin >> rel;
    for (int i = 1; i <= n; i++)
        villain[i] = (rel[i-1] == 'V');
    
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    set<segment> propos;
    
    for (int i = 1; i <= n; i++)
        if (villain[i]) {
            propos = get_propos(i);
            break;
        }
    
    auto result = *propos.begin();
    result.simplify();
    cout << result.x << " " << result.y << endl;
    
    return 0;
}
