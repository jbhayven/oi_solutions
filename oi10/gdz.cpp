#include <bits/stdc++.h>
#include "maja.h"
using namespace std;

const int MAX_N = 1000100;

vector<int> preproc(int max) {
    vector<bool> is_prime(max+1, true);
    vector<int> result;
    for(int i = 2; i <= max; i++)
        if(is_prime[i]) {
            result.push_back(i);
            for(int j = i; j <= max; j+=i)
                is_prime[j] = false;
        }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    auto primes = preproc(MAX_N);
    int limit;
    while((limit = gramy_dalej()) > 0) {
        int curr_num = 1;
        for(int p : primes) {
            if(curr_num > limit / p) break;
            while(curr_num <= limit / p && czy_podzielna_przez(curr_num * p))
                curr_num *= p;
        }
        zgaduj(curr_num);
    }
    return 0;
}
