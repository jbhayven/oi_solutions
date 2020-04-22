#include <bits/stdc++.h>
using namespace std;

#define REP(i, x) for(int i = 0; i < x; i++)
#define FOR(i, x) for(int i = 1; i <=x; i++)

const int MAX_N = 30100;

struct numTree {
    numTree* leftSon;
    numTree* rightSon;
    numTree* father;
    int value;
    size_t size;
    bool taken;
    
    numTree(int l, int r) {
        *this = numTree(l, r, nullptr);
    }
    
    numTree(int l, int r, numTree* father) {
        this->value = (l + r) / 2;
        this->size = (r - l + 1);
        this->father = father;
        this->taken = false;
        
        if(l < value) 
            leftSon = new numTree(l, value - 1, this);
        else leftSon = nullptr;
        
        if(value < r) 
            rightSon = new numTree(value + 1, r, this);
        else rightSon = nullptr;
    }
    
    static size_t get_size(numTree* ptr) {
        if(ptr == nullptr) return 0;
        return ptr -> size;
    }
    
    int get_ith_from_end(size_t i) {
        if(i > size) return -1;
        size--;
        
        if(i <= get_size(rightSon)) {
            return rightSon->get_ith_from_end(i);
        }
        else if(taken == false && i == get_size(rightSon) + 1) {
            taken = true;
            return value;
        }
        else return leftSon->get_ith_from_end(i - get_size(rightSon) - (taken == false));
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; 
    int a[MAX_N];
    int b[MAX_N];
    
    cin >> n; 
    FOR(i, n) cin >> b[i];
    
    numTree* tree = new numTree(1, n);
    
    for(int i = n; i > 0; i--) {
        a[i] = tree->get_ith_from_end(b[i] + 1);
        
        if(a[i] == -1) {
            cout << "NIE" << endl;
            return 0;
        }
    }
    
    FOR(i, n) cout << a[i] << endl;
    
    return 0;
}
