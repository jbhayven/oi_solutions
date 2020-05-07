#include <bits/stdc++.h>
using namespace std;

struct Block {
    static int block_cnt;
    Block* parent;
    
    Block() :
        parent(this) {
        block_cnt++;
    }
    
    Block* find() {
        if(parent == this) return this;
        return parent = parent->find();
    }
    
    void join(Block other) {
        Block* a = other.find();
        Block* b = this->find();
        
        if(a != b) {
            a->parent = b;
            block_cnt--;
        }
    }
};

int Block::block_cnt = 0;
    
struct Rectangle {
    pair<int, int> x;
    pair<int, int> y;
  
    Block* block;
    
    Rectangle() :
        block(new Block())
    {}
    
    void join(Rectangle &other) {
        block->join(*(other.block));
    }
};

inline bool are_together(Rectangle &r1, Rectangle &r2) {
    if(r1.x.first > r2.x.second) return false;  
    if(r1.y.first > r2.y.second) return false;  
    if(r2.x.first > r1.x.second) return false;  
    if(r2.y.first > r1.y.second) return false;  

    if(r1.x.first != r2.x.second && r1.x.second != r2.x.first) return true;
    if(r1.y.first != r2.y.second && r1.y.second != r2.y.first) return true;
        
    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    
    vector<Rectangle> rec(n);
    for(Rectangle &r : rec)
        cin >> r.x.first >> r.y.first >> r.x.second >> r.y.second;
    
    for(Rectangle &r1 : rec)
        for(Rectangle &r2 : rec)
            if(are_together(r1, r2))
                r1.join(r2);
    
    cout << Block::block_cnt << endl;
    
    return 0;
}
