#include <bits/stdc++.h>
using namespace std;

int cnt = 0;

struct FU {
    FU *par;
    list<int> bigs;
    
    FU *find() {
        return par == this ? this : par = par->find();
    }
    
    bool join(FU *other) {
        auto p1 = find();
        auto p2 = other->find();
        
        if (p1 == p2) 
            return false;
        
        cnt--;
        p1->par = p2;
        p2->bigs.splice(p2->bigs.end(), p1->bigs);
        return true;
    }
    
    FU (int size) : par(this), bigs({size}) {
        cnt++;
    }
};

struct QTree {
    QTree *sons[4];
    
    struct range_info {
        int l, r;
        FU *repr;
        
        range_info(int l, int r, FU *repr) :
            l, r, repr{}
    };
    
    struct treeInfo {
        list<range_info> top, bottom, left, right;
    } treeinf;
    
    QTree(int m, bool colored) {
        if (!colored) return;
        
        FU *repr = new FU(m);
        
        /* Add range infos */
    }
    
    QTree(int m, string &s, size_t &pos) {
        int type = s[pos++] - '0';
        switch(type) {
        case 0:
        case 1:
            *this = QTree(m, type);
            break;
        case 4:
            for (int i = 0; i < 4; i++)
                sons[i] = new QTree(m - 1, s, pos);
        }
    }
    
    QTree(int m, string &s) {
        size_t pos = 0;
        *this = QTree(m, s, pos);
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    
    return 0;
}
