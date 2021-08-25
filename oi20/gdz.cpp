#include <bits/stdc++.h>
#include "cgdzlib.h"
using namespace std;

const int MAX_N = 500100;
int n;

int test(int val) {
    int result = 0;
    for (int i = 2; i <= n; i++) {
        result += f(1, i, val);
    }
    return result;
}

int fnd(int i, int val) {
    for (int j = 1; j <= n; j++) {
        if (i == j) continue;
        if (f(i, j, val)) {
            return j;
        }
    }
    
    assert(false);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    n = inicjuj();
    
    if (n == 1) {
        odpowiedz(1);
        return 0;
    }
    
    int l = 1, r = n;
    while (l != r) {
        int s = (l + r) / 2;
        if (test(s) == 0) {
            r = s;
        } else {
            l = s + 1;
        }
    }
    
    int edge = fnd(1, l-1);
    int other = fnd(edge, n-1);
    
    if (g(edge, other))
        swap(edge, other);
        
    odpowiedz(edge);
    
    return 0;
}
