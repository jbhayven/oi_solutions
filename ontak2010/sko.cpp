#include <bits/stdc++.h>
using namespace std;

/* Mem limit: 32 MB */
const int MAX_N = 1.5e6 + 10;

int n;
int p[MAX_N];

void load() {
    /* Load and reorder so that p[i] < i holds for each i */
    struct {
        int u;
        int v;
        int next;
    } edge[MAX_N];
    int fst[MAX_N];
    
    int queue* = p;
    
    cin >> n;
    if (n == 1) {
        /* corner case */
        cout << 1 << endl;
        exit(0);
    }
    
    for (int i = 0; i < n; i++) {
        int a, b;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    load();
    
    
    
    return 0;
}
