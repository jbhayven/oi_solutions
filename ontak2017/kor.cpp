#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 201000;

struct Node {
    int in;
    int out;
    
    int pre;
    int post;
    list<Node*> children;
    
    void dfs(std::function<void(Node*)> preorder, 
             std::function<void(Node*)> postorder) {
                
        preorder(this);
        
        for(auto n : children)
            n -> dfs(preorder, postorder);
        
        postorder(this);
    }
};

void load_parents(vector<Node>& vec, int n) {
    vec.resize(n);
    for(int i = 1; i < n; i++) {
        int par; cin >> par;
        vec[par - 1].children.push_back(&vec[i]);
    }
}

class Tree { 
    int left, right;
    int val;
    
    Tree *l, *r;

    void make_children() {
        int s = (left + right) / 2;
        
        if (l == nullptr) 
            l = new Tree(left, s);
        if (r == nullptr)
            r = new Tree(s+1, right);
    }
public:
    void insert(int a) {
        val++;
        if (left == right) return;
        
        int s = (left + right) / 2;
        make_children();
        
        if (a <= s) l->insert(a);
        else r->insert(a);
    }
    
    int get(int a, int b) {
        if (a <= left && right <= b) return val;
        
        int s = (left + right) / 2;
        make_children();
        
        int ret = 0;
        if (a <= s) ret += l->get(a, b);
        if (s+1 <= b) ret += r->get(a, b);
        
        return ret;
    }
    
    Tree(int left, int right) :
        left(left),
        right(right),
        val(0),
        l(nullptr),
        r(nullptr)
    {}
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n;
    vector<Node> former;
    vector<Node> latter;
    
    cin >> n;
    
    load_parents(former, n);
    load_parents(latter, n);
    
    int visit_num = 0;
    former[0].dfs( 
        [&](Node *n){ n->in = visit_num++; }, 
        [&](Node *n){ n->out = visit_num++; }
    );
    
    for(int i = 0; i < n; i++) {
        latter[i].in = former[i].in;
        latter[i].out = former[i].out;
    }
    
    Tree *t = new Tree(0, visit_num);
    latter[0].dfs(
        [=](Node *n){ 
            n->pre = t->get(n->in, n->out); 
        },
        [=](Node *n){ 
            n->post = t->get(n->in, n->out);
            t->insert(n->in);            
        }
    );
    
    for(int i = 0; i < n; i++)
        cout << latter[i].post - latter[i].pre << " ";
    cout << endl;
    
    return 0;
}
