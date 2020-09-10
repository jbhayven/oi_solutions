#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int poww(long long a, long long p) {
    long long temp = 1;
    
    while (p) {
        if (p & 1) {
            temp *= a;
            temp %= MOD;
        }
        
        p >>= 1;
        a *= a;
        a %= MOD;
    }
    
    return temp;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    long long n, m, h;
    cin >> n >> m >> h;
    
    long long result = 0;
    
    for (int i = 0; i <= h; i++) {
        long long left = poww((i + 1), n) - poww(i, n);
        long long right = poww((i + 1), m) - poww(i, m);
        
        result += (left * right);
        result %= MOD;
    }
    
    if (result < 0) 
        result += MOD;
    
    cout << result << endl;
    
    return 0;
}
