#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e5 + 100;

bool is_square[MAX_N];
int num_primes[MAX_N];
int sieve[MAX_N];

void do_sieve() {
    for (int i = 2; i < MAX_N; i++) {
        if (sieve[i] == 0) {
            for (int j = i; j < MAX_N; j += i) {
                sieve[j] = i;
            }
        }
    }
    
    for (int i = 2; i < MAX_N; i++) {
        int j = i;
        int last = -1;
        while (j > 1) {
            if (sieve[j] == last) {
                is_square[i] = true;
                break;
            }
            
            num_primes[i]++;
            last = sieve[j];
            j /= sieve[j];
        }
    }
}

int64_t count_squ(int64_t limit) {
    int64_t result = 0;
    
    for (int64_t i = 2; i * i <= limit; i++) {
        if (is_square[i]) continue;
        
        if (num_primes[i] & 1) 
            result += limit / (i * i);
        else
            result -= limit / (i * i);
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    do_sieve();
    
    int64_t n; cin >> n;
    int64_t l = 1, r = n * 4;
    
    while (l != r) {
        int64_t s = (l + r ) / 2;
        if (count_squ(s) >= n) {
            r = s;
        } else {
            l = s + 1;
        }
    }
    
    cout << l << endl;
    
    return 0;
}
