#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e7 + 100;

int n; 
int aa[MAX_N];
int bb[MAX_N];
int *a = aa + 10;
int *b = bb + 10;

int fibs[] = {
    1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89
};

inline void add_1(int *tab, int pos) {
    while(tab[pos + 1]) {
        tab[pos + 1] = 0;
        pos += 2;
    }
    
    if (tab[pos - 1]) {
        tab[pos - 1] = 0;
        pos++;
    }
    
    while(tab[pos + 1]) {
        tab[pos + 1] = 0;
        pos += 2;
    }
    
    tab[pos] = 1;
}

void finalize(int div) {
    int as_int = 0;
    for (int i = 7; i > 0; i--)
        if (a[i] == 1) as_int += fibs[i];
    
    as_int /= div;
    for (int i = 7; i > 0; i--)
        if (as_int >= fibs[i]) {
            b[i] = 1;
            as_int -= fibs[i];
        }
    
    while(n > 1 && b[n] != 1) n--;
}

void k_2() {
    for (int i = n; i > 7; i--) {
        if (a[i] != 1) continue;
        
        a[i] = 0;
        add_1(b, i-2);
        
        if (a[i-3]) {
            a[i-3] = 0;
            add_1(b, i-3);
        } else {
            add_1(a, i-3);
        }
    } 
    
    finalize(2);
}

void k_3() {
    for (int i = n; i > 7; i--) {
        if (a[i] != 1) continue;
        
        a[i] = 0;
        add_1(b, i-3);
        
        if (a[i-2]) {
            a[i-2] = 0;
            add_1(b, i-2);
            add_1(a, i-3);
        } else if (a[i-3]) {
            a[i-2] = 1;
            a[i-3] = 0;
            add_1(a, i-4);
            add_1(b, i-3);
        } else if (a[i-4]) {
            add_1(b, i-2);
            a[i-4] = 0;
        } else if (a[i-5]) {
            a[i-2] = 1;
            a[i-5] = 0;
            add_1(b, i-3);
        } else if (a[i-6]) {
            a[i-4] = 1;
            add_1(b, i-3);
            add_1(b, i-6);
            add_1(a, i-4);
            add_1(a, i-7);
        } else {
            
            add_1(b, i-4);
        }
    } 
    
    finalize(3);
}

void solve() {
    cin >> n;
    
    for (int i = 1; i <= max(10, n + 10); i++) {
        /* cleanup */
        a[i] = 0;
        b[i] = 0;
    }
        
    for (int i = 1; i <= n; i++) 
        cin >> a[i];
        
    int k; cin >> k;
    
    if (k == 2) k_2();
    else if (k == 3) k_3();

    cout << n << " ";
    for (int i = 1; i <= n; i++)
        cout << b[i] << " ";
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int z; cin >> z;
    
    while(z--) {
        solve();
    }
    
    return 0;
}
