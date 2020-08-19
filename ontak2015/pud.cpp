#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100010;
const int MOD = 1e9 + 33;

int fact[MAX_N];
int anti_fact[MAX_N];

int quick_pow(int a, int pow) {
    long long mno = a;
    long long result = 1;
    
    while (pow) {
        if (pow & 1) {
            result *= mno;
            result %= MOD;
        }
        
        mno *= mno;
        mno %= MOD;
        pow >>= 1;
    }
    
    return result;
}

void init_facts() {
    fact[0] = 1;
    for (int i = 1; i < MAX_N; i++) 
        fact[i] = (long long) fact[i-1] * i % MOD;
        
    for (int i = 0; i < MAX_N; i++)
        anti_fact[i] = quick_pow(fact[i], MOD - 2);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, k; cin >> n >> k;
    vector<int> nums(k);
    for (int &i : nums) cin >> i;
    
    init_facts();
    
    int result[MAX_N];
    result[0] = 1;
    int grand_total = 1; // (1 / 0!) * res_0 + (1 / 1!) * res_1 + (1 / 2!) * res_2 + ... + (1 / n!) * res_n
    
    for (int i = 1; i <= n; i++) {
        int temp_total = grand_total;
        for (int num : nums) {
            if (num > i) continue;
            
            long long temp = result[i - num];
            temp *= anti_fact[i-num];
            temp %= MOD;
            
            temp_total -= temp;
            temp_total += MOD;
            temp_total %= MOD;
        }
        
        result[i] = (long long) temp_total * fact[i-1] % MOD;
        
        long long temp = result[i];
        temp *= anti_fact[i];
        temp %= MOD;
        
        grand_total += temp;
        grand_total %= MOD;
    }
    
    cout << result[n] << endl;
    
    return 0;
}
